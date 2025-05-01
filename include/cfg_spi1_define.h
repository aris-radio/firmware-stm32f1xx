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
 * @file    cfg_spi1_define.h
 * @brief   Configuration definitions for SPI1 and LoRa interfaces.
 *          According to the ARIS Alliance standard. The firmware core must support at least 2 LoRa interfaces.
 *          When only one LoRa interface is used, the second one must be disabled. This can be done by defining -DSINGLE_COMM_INTERFACE
 *          in the compiler options.
 * @author  ARIS Alliance
 *
 */

#ifndef __CFG_SPI1_DEFINE_H
#define __CFG_SPI1_DEFINE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h"

/* ===== SPI1 - Shared Pins ===== */
#define SPI1_SCK_GPIO_PORT GPIOA
#define SPI1_SCK_PIN GPIO_PIN_5

#define SPI1_MISO_GPIO_PORT GPIOA
#define SPI1_MISO_PIN GPIO_PIN_6

#define SPI1_MOSI_GPIO_PORT GPIOA
#define SPI1_MOSI_PIN GPIO_PIN_7

/* ===== SPI NSS (Chip Select) - Separate Pins for Each Interface ===== */
#define SPI1_NSS_GPIO_PORT GPIOA

#define SPI1_NSS_IN1_PIN GPIO_PIN_4 /* NSS for Interface 1 */
#ifndef SINGLE_COMM_INTERFACE
    #define SPI1_NSS_IN2_PIN GPIO_PIN_2 /* NSS for Interface 2 */
#endif

/* ===== SPI RESET - Separate Pins for Each Interface ===== */
#define SPI1_RESET_GPIO_PORT GPIOA

#define SPI1_RESET_IN1_PIN GPIO_PIN_3 /* Reset for Interface 1 */
#ifndef SINGLE_COMM_INTERFACE
    #define SPI1_RESET_IN2_PIN GPIO_PIN_1 /* Reset for Interface 2 */
#endif

/* ===== SPI DIO0 (Interrupt Pin) - Shared ===== */
#define SPI1_DIO0_GPIO_PORT GPIOB
#define SPI1_DIO0_PIN GPIO_PIN_0

/* ******************* INTERFACE 1 **************************** */
/**
 * @brief  Reset LoRa interface 1 module
 */
#define MX_SPI1_Reset_Interface1() MX_SPI1_Reset_Interface(SPI1_RESET_IN1_PIN)

/**
 * @brief  Select LoRa interface 1 for SPI communication
 */
#ifdef SINGLE_COMM_INTERFACE
    #define MX_SPI1_Select_Interface1() MX_SPI1_Select_Interface(SPI1_NSS_IN1_PIN)
#else
    #define MX_SPI1_Select_Interface1() MX_SPI1_Select_Interface(SPI1_NSS_IN1_PIN, SPI1_NSS_IN2_PIN)
#endif

/**
 * @brief  Unselect LoRa interface 1
 */
#define MX_SPI1_Unselect_Interface1() MX_SPI1_Unselect_Interface(SPI1_NSS_IN1_PIN)

#ifndef SINGLE_COMM_INTERFACE
    /* ******************* INTERFACE 2 **************************** */
    /**
     * @brief  Reset LoRa interface 2 module
     */
    #define MX_SPI1_Reset_Interface2() MX_SPI1_Reset_Interface(SPI1_RESET_IN2_PIN)

    /**
     * @brief  Select LoRa interface 2 for SPI communication
     */
    #define MX_SPI1_Select_Interface2() MX_SPI1_Select_Interface(SPI1_NSS_IN2_PIN, SPI1_NSS_IN1_PIN)

    /**
     * @brief  Unselect LoRa interface 2
     */
    #define MX_SPI1_Unselect_Interface2() MX_SPI1_Unselect_Interface(SPI1_NSS_IN2_PIN)
#endif



/* ************** FUNCTIONS **************** */

    /**
     * @brief  Initializes SPI1 in Master mode, SPI mode 0 (CPOL=0, CPHA=0).
     */
    void MX_SPI1_Init(void);

    /**
     * @brief  Force reset SPI1 peripheral.
     */
    void MX_SPI1_ForceReset(void);

    /**
     * @brief  Reset a specific LoRa interface module.
     * @param  reset_pin GPIO pin for the reset signal.
     */
    void MX_SPI1_Reset_Interface(uint16_t reset_pin);

    /**
     * @brief  Select a specific LoRa interface for SPI communication.
     * @param  select_pin GPIO pin to activate the selected interface.
     * @param  deselect_pin GPIO pin to deactivate the other interface. If flag SINGLE_COMM_INTERFACE is defined, this parameter is not used.
     */
    void MX_SPI1_Select_Interface(uint16_t select_pin
#ifndef SINGLE_COMM_INTERFACE
        , uint16_t deselect_pin
#endif
        );

    /**
     * @brief  Unselect a specific LoRa interface.
     * @param  select_pin GPIO pin to deactivate the interface.
     */
    void MX_SPI1_Unselect_Interface(uint16_t select_pin);

#ifdef __cplusplus
}
#endif

#endif /* __CFG_SPI1_DEFINE_H */
