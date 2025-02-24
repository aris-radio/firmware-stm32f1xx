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
 * @file    cfg_gpio_define.c
 * @brief   Config the gpio pins for the stm32f1xx
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */

#include "stm32f1xx_hal.h"
#include "cfg_spi1_define.h"
#include "cfg_gpio_define.h"


GPIO_InitTypeDef GPIO_InitStruct;

/**
 * @brief  Initializes GPIO pins.
 */
/**
 * @brief  Initializes GPIO pins.
 */
void MX_GPIO_Init(void)
{
    /* Enable Clocks for GPIOA, GPIOB, GPIOC */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* ===== SPI1 GPIO Configuration (Shared) ===== */
    GPIO_InitStruct.Pin   = SPI1_SCK_PIN | SPI1_MOSI_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = SPI1_MISO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* ===== LoRa NSS (Chip Select) - Separate for each module ===== */
    GPIO_InitStruct.Pin   = SPI1_NSS_433_PIN | SPI1_NSS_868_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI1_NSS_GPIO_PORT, &GPIO_InitStruct);

    /* Set both NSS high (deselect both modules at startup) */
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_433_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_PORT, SPI1_NSS_868_PIN, GPIO_PIN_SET);

    /* ===== LoRa RESET - Separate for each module ===== */
    GPIO_InitStruct.Pin   = SPI1_RESET_433_PIN | SPI1_RESET_868_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI1_RESET_GPIO_PORT, &GPIO_InitStruct);

    /* Set both RESET high (not in reset state) */
    HAL_GPIO_WritePin(SPI1_RESET_GPIO_PORT, SPI1_RESET_433_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SPI1_RESET_GPIO_PORT, SPI1_RESET_868_PIN, GPIO_PIN_SET);

    /* ===== LoRa DIO0 (Interrupt Pin) - Shared ===== */
    GPIO_InitStruct.Pin   = SPI1_DIO0_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(SPI1_DIO0_GPIO_PORT, &GPIO_InitStruct);

    /* ===== LED on PC13 ===== */
    GPIO_InitStruct.Pin   = GPIO_PIN_13;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}



/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/ 