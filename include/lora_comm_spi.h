/**
 *  @attention
 *  Copyright (C) 2025  - ARIS Alliance
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
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ******************************************************************************
 * @file    lora_comm_spi.h
 * @brief   LoRa communication via SPI
 * @author  ARIS Alliance
 *
 */

#ifndef __LORA_COMM_SPI_H
#define __LORA_COMM_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include "stm32f1xx_hal.h"

#define REG_FIFO                    0x00
#define REG_OP_MODE                 0x01
#define REG_FRF_MSB                 0x06
#define REG_FRF_MID                 0x07
#define REG_FRF_LSB                 0x08
#define REG_PA_CONFIG               0x09
#define REG_PA_DAC                  0x4D
#define REG_LNA                     0x0c
#define REG_FIFO_ADDR_PTR           0x0d
#define REG_FIFO_TX_BASE_ADDR       0x0e
#define REG_FIFO_RX_BASE_ADDR       0x0f
#define REG_FIFO_RX_CURRENT_ADDR    0x10
#define REG_IRQ_FLAGS_MASK          0x11
#define REG_IRQ_FLAGS               0x12
#define REG_RX_NB_BYTES             0x13
#define REG_PKT_SNR_VALUE           0x19
#define REG_PKT_RSSI_VALUE          0x1a
#define REG_MODEM_CONFIG_1          0x1d
#define REG_MODEM_CONFIG_2          0x1e
#define REG_PREAMBLE_MSB            0x20
#define REG_PREAMBLE_LSB            0x21
#define REG_PAYLOAD_LENGTH          0x22
#define REG_MODEM_CONFIG_3          0x26
#define REG_RSSI_WIDEBAND           0x2c
#define REG_DETECTION_OPTIMIZE      0x31
#define REG_DETECTION_THRESHOLD     0x37
#define REG_SYNC_WORD               0x39
#define REG_DIO_MAPPING_1           0x40
#define REG_VERSION                 0x42

// PA_DAC register values
#define PA_DAC_DEFAULT              0x84  // Normal mode (max 17 dBm)
#define PA_DAC_HIGH_POWER           0x87  // High Power Mode (allows 20 dBm)


/*
 * Transceiver modes
 */
#define MODE_LONG_RANGE_MODE        0x80
#define MODE_SLEEP                  0x00
#define MODE_STDBY                  0x01
#define MODE_TX                     0x03
#define MODE_RX_CONTINUOUS          0x05
#define MODE_RX_SINGLE              0x06

#define FREQ_STEP                   61.03515625 // Frequency step size (61.035 Hz per step)

    /* LoRa Module Type */
    typedef enum
    {
        LORA_INTERFACE1,
        LORA_INTERFACE2
    } LoRa_Module_t;

    /**
     * @brief Define the SPI handle externally
     */
    extern SPI_HandleTypeDef hspi1;

    /* ******************* LoRa Register Operations ************************** */

    /**
     * @brief  Reads a LoRa register.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  addr: Register address.
     * @param  data: Pointer to store the read data.
     * @param  len: Number of bytes to read.
     */
    void LoRa_GetReg(LoRa_Module_t interface, uint8_t addr, uint8_t *data, uint8_t len);

    /**
     * @brief  Writes to a LoRa register.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  addr: Register address.
     * @param  data: Pointer to the data to write.
     * @param  len: Number of bytes to write.
     */
    void LoRa_SetReg(LoRa_Module_t interface, uint8_t addr, uint8_t *data, uint8_t len);

    /* ******************* LoRa Configuration ************************** */

    /**
     * @brief  Gets the frequency of a LoRa module.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @return Frequency in Hz.
     */
    uint32_t LoRa_GetFrequency(LoRa_Module_t interface);

    /**
     * @brief  Sets the spreading factor and bandwidth for LoRa communication.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  sf: Spreading Factor (Valid: 6 to 12).
     * @param  bw: Bandwidth (Valid: 0 to 9 as per SX1278 datasheet).
     */
    void LoRa_SetSF_BW(LoRa_Module_t interface, uint8_t sf, uint8_t bw);

    /**
     * @brief  Gets the spreading factor (SF) and bandwidth (BW) from a LoRa module.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  sf: Pointer to store Spreading Factor.
     * @param  bw: Pointer to store Bandwidth.
     */
    void LoRa_GetSF_BW(LoRa_Module_t interface, uint8_t *sf, uint8_t *bw);

    /* ******************* LoRa Modes ************************** */

    /**
     * @brief  Sets LoRa module to Standby mode.
     * The module is idle and ready to switch states quickly.
     */
    void LoRa_ModeIdle(LoRa_Module_t interface);

    /**
     * @brief  Sets LoRa module to Sleep mode.
     * This minimizes power consumption, but FIFO is lost.
     */
    void LoRa_ModeSleep(LoRa_Module_t interface);

    /**
     * @brief  Sets LoRa module to Continuous Receive mode.
     * The module will listen for incoming packets.
     */
    void LoRa_ModeReceive(LoRa_Module_t interface);

    /**
     * @brief  Sets LoRa module to Continuous Receive mode.
     * The module will listen for incoming packets.
     */
    void LoRa_ModeTransmit(LoRa_Module_t interface)

    /**
     * @brief  Sets the transmission power level for LoRa.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  level: Transmission power level (2-20 dBm).
     */
    void LoRa_SetTxPower(LoRa_Module_t interface, int level);

    /* ******************* LoRa Data Transmission ************************** */

    /**
     * @brief  Sends data via LoRa.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  data: Pointer to the data to send.
     * @param  len: Length of the data.
     */
    void LoRa_SendData(LoRa_Module_t interface, uint8_t *data, uint8_t len);

    /**
     * @brief  Receives data via LoRa.
     * @param  interface: The LoRa interface (LORA_INTERFACE1 or LORA_INTERFACE2).
     * @param  buffer: Pointer to store received data.
     * @param  len: Expected data length.
     */
    void LoRa_ReceiveData(LoRa_Module_t interface, uint8_t *buffer, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* __LORA_COMM_SPI_H */
