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
 * @file    cfg_spi2_define.h
 * @brief   Configuration definitions for SPI2 for external communication.
 * @author  ARIS Alliance
 *
 */

#ifndef __CFG_SPI2_DEFINE_H
#define __CFG_SPI2_DEFINE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h"

#define SPI2_SCK_PIN        GPIO_PIN_13
#define SPI2_SCK_GPIO_PORT  GPIOB
#define SPI2_MISO_PIN       GPIO_PIN_14
#define SPI2_MISO_GPIO_PORT GPIOB
#define SPI2_MOSI_PIN       GPIO_PIN_15
#define SPI2_MOSI_GPIO_PORT GPIOB
#define SPI2_NSS_PIN        GPIO_PIN_12
#define SPI2_NSS_GPIO_PORT  GPIOB
#define SPI2_RESET_PIN      GPIO_PIN_11
#define SPI2_RESET_GPIO_PORT GPIOB

// Interrupt PIN
#define SPI2_DIO0_PIN       GPIO_PIN_10
#define SPI2_DIO0_GPIO_PORT GPIOB

/* ************** FUNCTIONS **************** */

    /**
     * @brief  Initializes SPI2 in Slave mode
     */
    void MX_SPI2_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* __CFG_SPI2_DEFINE_H */
