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

// Frequency defines
#define LORA_FREQ_433 433000000
#define LORA_FREQ_868 868000000

typedef enum {
    LORA_433MHz,
    LORA_868MHz
} LoRa_Module_t;


/**
 * @brief  Resets the LoRa module. For frequency 433 MHz.
 * @retval None
 */
void LoRa_Reset433(void);

/**
 * @brief  Resets the LoRa module. For frequency 868 MHz.
 * @retval None
 */
void LoRa_Reset868(void);


#ifdef __cplusplus
}
#endif

#endif /* __LORA_COMM_SPI_H */