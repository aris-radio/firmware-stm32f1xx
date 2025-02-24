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
 * @file    lora_comm_spi.c
 * @brief   LoRa communication via SPI
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */
#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "lora_comm_spi.h"
#include "cfg_spi1_define.h"

/**
 * @brief  Resets the LoRa module. For frequency 433 MHz.
 */
void LoRa_Reset433(void)
{
    MX_SPI1_Reset_433();
}

/**
 * @brief  Resets the LoRa module. For frequency 868 MHz.
 */
void LoRa_Reset868(void)
{
    MX_SPI1_Reset_868();
}

/* ************************************************************** */


void LoRa_Comm_Send(LoRa_Module_t module, uint8_t *data, uint16_t size)





 
 /************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/ 