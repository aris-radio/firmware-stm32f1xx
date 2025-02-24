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
 * @file    cfg_spi1_define.c
 * @brief   Config definitions for SPI1.
 * @author  ARIS Alliance
 *
 */


#ifndef __CFG_SPI1_DEFINE_H
#define __CFG_SPI1_DEFINE_H


#ifdef __cplusplus
extern "C" {
#endif

/* SPI1 NSS (Chip Select) Pin */
#define SPI1_NSS_GPIO_PORT     GPIOA
#define SPI1_NSS_PIN           GPIO_PIN_4

#define SPI1_RESET_GPIO_PORT   GPIOA
#define SPI1_RESET_PIN         GPIO_PIN_3

#define SPI1_DIO0_GPIO_PORT    GPIOB
#define SPI1_DIO0_PIN          GPIO_PIN_0

#define SPI1_SCK_GPIO_PORT     GPIOA
#define SPI1_SCK_PIN           GPIO_PIN_5

#define SPI1_MISO_GPIO_PORT    GPIOA
#define SPI1_MISO_PIN          GPIO_PIN_6

#define SPI1_MOSI_GPIO_PORT    GPIOA
#define SPI1_MOSI_PIN          GPIO_PIN_7


/**
  * @brief  Initializes SPI1 in Master mode, SPI mode 0 (CPOL=0, CPHA=0).
  *         - Baud rate prescaler: SPI_BAUDRATEPRESCALER_8 (8 MHz if MCU=64 MHz)
  *         - NSS: software-managed (SPI_NSS_SOFT)
  *         - First bit: MSB
  * @retval None
  */
void MX_SPI1_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __CFG_SPI1_DEFINE_H */