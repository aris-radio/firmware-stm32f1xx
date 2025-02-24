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

#include "stm32f1xx_hal.h"
#include "err_handle.h"
#include "cfg_spi1_define.h"


SPI_HandleTypeDef hspi1;

/**
 * @brief  Initializes SPI1 in Master mode, SPI mode 0 (CPOL=0, CPHA=0).
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
}



/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/ 