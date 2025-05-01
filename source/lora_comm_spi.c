/**
 *  @attention
 *  Copyright (C) 2025 - ARIS Alliance
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 ******************************************************************************
 * @file    lora_comm_spi.c
 * @brief   LoRa communication via SPI
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */

#include "lora_comm_spi.h"
#include "cfg_spi1_define.h"

/* ******************* LoRa Register Operations ************************** */

void LoRa_GetReg(LoRa_Module_t interface, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t addr_read = addr | 0x80; // Set MSB to 1 for read operation

    (interface == LORA_INTERFACE1) ? MX_SPI1_Select_Interface1() : MX_SPI1_Select_Interface2();

    HAL_SPI_Transmit(&hspi1, &addr_read, 1, 1000);
    HAL_SPI_Receive(&hspi1, data, len, 1000);

    (interface == LORA_INTERFACE1) ? MX_SPI1_Unselect_Interface1() : MX_SPI1_Unselect_Interface2();
}

void LoRa_SetReg(LoRa_Module_t interface, uint8_t addr, uint8_t *data, uint8_t len)
{
    uint8_t addr_write = addr & 0x7F; // Set MSB to 0 for write operation

    (interface == LORA_INTERFACE1) ? MX_SPI1_Select_Interface1() : MX_SPI1_Select_Interface2();

    HAL_SPI_Transmit(&hspi1, &addr_write, 1, 1000);
    HAL_SPI_Transmit(&hspi1, data, len, 1000);

    (interface == LORA_INTERFACE1) ? MX_SPI1_Unselect_Interface1() : MX_SPI1_Unselect_Interface2();
}

/* ******************* LoRa Configuration ************************** */

uint32_t LoRa_GetFrequency(LoRa_Module_t interface)
{
    uint8_t freq_regs[3];
    LoRa_GetReg(interface, REG_FRF_MSB, freq_regs, 3);

    uint32_t freq_value = ((uint32_t)freq_regs[0] << 16) |
                          ((uint32_t)freq_regs[1] << 8) |
                          ((uint32_t)freq_regs[2]);

    return (uint32_t)(freq_value * FREQ_STEP);
}

void LoRa_SetSF_BW(LoRa_Module_t interface, uint8_t sf, uint8_t bw)
{
    uint8_t modem_config1, modem_config2;

    LoRa_GetReg(interface, REG_MODEM_CONFIG_1, &modem_config1, 1);
    LoRa_GetReg(interface, REG_MODEM_CONFIG_2, &modem_config2, 1);

    modem_config1 = (modem_config1 & 0x0F) | (bw << 4);
    modem_config2 = (modem_config2 & 0x0F) | (sf << 4);

    LoRa_SetReg(interface, REG_MODEM_CONFIG_1, &modem_config1, 1);
    LoRa_SetReg(interface, REG_MODEM_CONFIG_2, &modem_config2, 1);
}

/* ******************* LoRa Get Spreading Factor & Bandwidth ************************** */

void LoRa_GetSF_BW(LoRa_Module_t interface, uint8_t *sf, uint8_t *bw)
{
    uint8_t modem_config1, modem_config2;

    LoRa_GetReg(interface, REG_MODEM_CONFIG_1, &modem_config1, 1);
    LoRa_GetReg(interface, REG_MODEM_CONFIG_2, &modem_config2, 1);

    *bw = (modem_config1 >> 4) & 0x0F; // BW is in bits 7-4
    *sf = (modem_config2 >> 4) & 0x0F; // SF is in bits 7-4
}

/* ******************* LoRa Modes ************************** */

void LoRa_ModeIdle(LoRa_Module_t interface)
{
    uint8_t mode = MODE_LONG_RANGE_MODE | MODE_STDBY;
    LoRa_SetReg(interface, REG_OP_MODE, &mode, 1);
}

void LoRa_ModeSleep(LoRa_Module_t interface)
{
    uint8_t mode = MODE_LONG_RANGE_MODE | MODE_SLEEP;
    LoRa_SetReg(interface, REG_OP_MODE, &mode, 1);
}

void LoRa_ModeReceive(LoRa_Module_t interface)
{
    uint8_t mode = MODE_LONG_RANGE_MODE | MODE_RX_CONTINUOUS;
    LoRa_SetReg(interface, REG_OP_MODE, &mode, 1);
}

void LoRa_ModeTransmit(LoRa_Module_t interface)
{
    uint8_t mode = MODE_LONG_RANGE_MODE | MODE_TX;
    LoRa_SetReg(interface, REG_OP_MODE, &mode, 1);
}


void LoRa_SetTxPower(LoRa_Module_t interface, int level)
{
    uint8_t pa_config;
    uint8_t pa_dac;

    // Ensure the power level is within the valid range (2-20 dBm)
    if (level < 2)
        level = 2;
    if (level > 20)
        level = 20;

    if (level > 17)
    {
        // For 18-20 dBm, enable High Power Mode in REG_PA_DAC
        pa_config = 0x80 | 15;  // PA_BOOST with max level (15 corresponds to 20 dBm)
        pa_dac = PA_DAC_HIGH_POWER;          // Enable High Power Mode
    }
    else
    {
        // For 2-17 dBm, adjust the power level normally
        pa_config = 0x80 | (level - 2);  // PA_BOOST with adjusted level
        pa_dac = PA_DAC_DEFAULT;                   // Normal configuration
    }

    // Write to REG_PA_CONFIG to set the transmission power
    LoRa_SetReg(interface, REG_PA_CONFIG, &pa_config, 1);

    // Check current REG_PA_DAC value and update only if necessary
    uint8_t current_pa_dac;
    LoRa_GetReg(interface, REG_PA_DAC, &current_pa_dac, 1);
    if (current_pa_dac != pa_dac)
    {
        LoRa_SetReg(interface, REG_PA_DAC, &pa_dac, 1);
    }
}


/* ******************* LoRa Data Transmission ************************** */

void LoRa_SendData(LoRa_Module_t interface, uint8_t *data, uint8_t len)
{
    // Placeholder for sending data
}

void LoRa_ReceiveData(LoRa_Module_t interface, uint8_t *buffer, uint8_t len)
{
    // Placeholder for receiving data
}





/* ************ LoRa Async (Interruption) Pasive listen ***************** */
void LoRa_EnableReceiveInterrupt(LoRa_Module_t interface)
{
    uint8_t reg_value;

    // 1) Clear any pending IRQ flags
    //    Writing '1' to the relevant bits clears the flags.
    reg_value = 0xFF;  // Write '1' to all bits to clear any active flags
    LoRa_SetReg(interface, REG_IRQ_FLAGS, &reg_value, 1);

    // 2) Unmask the desired interrupts.
    //    Masked = 1 (disabled), Unmasked = 0 (enabled).
    //    If you only want RxDone, ensure its corresponding bit is 0.
    //    RxDone corresponds to bit 6 of IRQ_FLAGS_MASK (0x40).
    //    For simplicity, we set everything to 0x00, enabling all interrupts.
    reg_value = 0x00;
    LoRa_SetReg(interface, REG_IRQ_FLAGS_MASK, &reg_value, 1);

    // 3) Configure DIO0 to trigger an interrupt upon packet reception (RxDone).
    //    DIO0 mapped to RxDone -> "00" in bits [7:6].
    LoRa_GetReg(interface, REG_DIO_MAPPING_1, &reg_value, 1);
    reg_value &= 0x3F;  // Clear bits 7:6 (DIO0 mapping)
    // With "00" in bits 7:6, DIO0 is linked to RxDone
    LoRa_SetReg(interface, REG_DIO_MAPPING_1, &reg_value, 1);

    // 4) Set the module to Continuous Receive mode
    LoRa_ModeReceive(interface);

    // At this point, once a packet is received, DIO0 will go high,
    // triggering the external interrupt in your MCU. In the ISR (interrupt
    // service routine), you can read the received data and clear the IRQ flags.
}



/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/
