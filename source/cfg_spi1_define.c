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
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ******************************************************************************
 * @file    cfg_spi1_define.c
 * @brief   Config definitions for SPI1.
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "err_handle.h"
#include "base_config.h"
#include "cfg_spi1_define.h"
#include "lora_comm_spi.h"


SPI_HandleTypeDef hspi1;

/**
 * @brief  Initializes SPI1 in Master mode, SPI mode 0 (CPOL=0, CPHA=0) and configures both LoRa interfaces.
 */
void MX_SPI1_Init(void)
{
    /* Enable SPI1 clock */
    __HAL_RCC_SPI1_CLK_ENABLE();

    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW; // CPOL=0
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;     // CPHA=0 -> SPI mode 0
    hspi1.Init.NSS = SPI_NSS_SOFT;             // Software-managed NSS
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    /*
       If your MCU is running at 64 MHz, with prescaler=8, SPI speed would be 8 MHz.
       Make sure it does not exceed what your RF96/SX1278 supports. If needed, lower
       the speed by using PRESCALER_16, PRESCALER_32, etc.
    */
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }

    /* Reset LoRa Interfaces */
    MX_SPI1_Reset_Interface(SPI1_RESET_IN1_PIN);
#ifndef SINGLE_COMM_INTERFACE
    MX_SPI1_Reset_Interface(SPI1_RESET_IN2_PIN);
#endif

    /* ******************* Initialize Both LoRa Interfaces ************************** */
    for (LoRa_Module_t interface = LORA_INTERFACE1; 
#ifndef SINGLE_COMM_INTERFACE
         interface <= LORA_INTERFACE2; 
#else
         interface <= LORA_INTERFACE1; 
#endif
    interface++)
    {
        uint8_t version = 0;
        uint8_t attempts = 0;

        /* Check LoRa version */
        while (attempts++ < TIMEOUT_RESET) 
        {
            LoRa_GetReg(interface, REG_VERSION, &version, 1);
            if (version == 0x12) 
                break;
            __NOP();  // No operation, avoids unnecessary function call delays
        }

        if (attempts >= TIMEOUT_RESET)
        {
            Error_Handler();
        }

        /* ******************* Default LoRa Configuration ************************** */
        LoRa_Sleep(interface);  // Put LoRa module in sleep mode before configuring

        /* Default register values */
        const uint8_t default_config[][2] = {
            {REG_FIFO_RX_BASE_ADDR, 0x00}, // Set FIFO RX Base Address
            {REG_FIFO_TX_BASE_ADDR, 0x00}, // Set FIFO TX Base Address
            {REG_LNA, 0x03},               // Enable maximum gain
            {REG_MODEM_CONFIG_3, 0x04}     // Enable Low Data Rate Optimization
        };

        /* Apply default configuration */
        for (uint8_t i = 0; i < sizeof(default_config) / sizeof(default_config[0]); i++)
        {
            LoRa_SetReg(interface, default_config[i][0], &default_config[i][1], 1);
        }

        /* Set Transmission Power to Maximum (20 dBm) */
        LoRa_SetTxPower(interface, 20);

        /* Set LoRa to Standby Mode (Idle) */
        LoRa_Idle(interface);
    }
}


/**
 * @brief  Force reset SPI1 peripheral
 */
void MX_SPI1_ForceReset(void)
{
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();
}

/**
 * @brief  Reset a specific LoRa interface module
 */
static inline void MX_SPI1_Reset_Interface(uint16_t reset_pin)
{
    HAL_GPIO_WritePin(SPI1_RESET_GPIO_PORT, reset_pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(SPI1_RESET_GPIO_PORT, reset_pin, GPIO_PIN_SET);
    HAL_Delay(5);
}

/**
 * @brief  Select a specific LoRa interface for SPI communication
 */
static inline void MX_SPI1_Select_Interface(uint16_t select_pin
#ifndef SINGLE_COMM_INTERFACE
    , uint16_t deselect_pin
#endif
)
{
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, select_pin, GPIO_PIN_RESET);  // Activate selected interface
#ifndef SINGLE_COMM_INTERFACE
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, deselect_pin, GPIO_PIN_SET);  // Deactivate the other
#endif
}

/**
 * @brief  Unselect a specific LoRa interface
 */
static inline void MX_SPI1_Unselect_Interface(uint16_t select_pin)
{
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, select_pin, GPIO_PIN_SET);  // Deactivate interface
}



/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/ 