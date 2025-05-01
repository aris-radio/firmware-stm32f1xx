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
 * @file    cfg_sp21_define.c
 * @brief   Config definitions for SPI2.
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

SPI_HandleTypeDef hspi2;

/**
 * @brief  Initializes SPI2 in Slave mode, SPI mode 0 (CPOL=0, CPHA=0).
 */
void MX_SPI2_Init(void)
{
    /* Enable SPI2 Clock */
    __HAL_RCC_SPI2_CLK_ENABLE();

    /* Configure SPI2 parameters */
    hspi2.Instance               = SPI2;
    hspi2.Init.Mode              = SPI_MODE_SLAVE;               // Set SPI2 as Slave
    hspi2.Init.Direction         = SPI_DIRECTION_2LINES;         // Full-duplex communication
    hspi2.Init.DataSize          = SPI_DATASIZE_8BIT;            // 8-bit data size
    hspi2.Init.CLKPolarity       = SPI_POLARITY_LOW;             // Clock idle state is LOW
    hspi2.Init.CLKPhase          = SPI_PHASE_1EDGE;              // Data sampled on the first edge
    hspi2.Init.NSS               = SPI_NSS_HARD_INPUT;           // NSS handled by hardware (controlled by Master)
    hspi2.Init.FirstBit          = SPI_FIRSTBIT_MSB;             // Most significant bit sent first
    hspi2.Init.TIMode            = SPI_TIMODE_DISABLE;           // TI mode disabled
    hspi2.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;   // CRC calculation disabled
    hspi2.Init.CRCPolynomial     = 7;                            // Default CRC polynomial (not used)

    /* Initialize SPI2 with the configured parameters */
    if (HAL_SPI_Init(&hspi2) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
    }
}

/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/