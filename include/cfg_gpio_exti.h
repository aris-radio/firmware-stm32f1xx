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
 * @file    cfg_gpio_exti.c
 * @brief   Interruption functions for GPIO pins.
 * @author  ARIS Alliance
 */

#ifndef __CFG_GPIO_EXTI_H
#define __CFG_GPIO_EXTI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @brief Interrupt handler for EXTI0 line.
 * 
 * This function is executed when an interrupt is detected on the EXTI0 pin,
 * which in this case is connected to DIO0 of the LoRa module. It calls the
 * HAL_GPIO_EXTI_IRQHandler() function to handle the interrupt in a standard way.
 */
void EXTI0_IRQHandler(void);

/**
 * @brief External GPIO interrupt callback.
 * 
 * This function is called by HAL when an event is detected on an EXTI line.
 * If the interrupt originates from the pin assigned to DIO0 of the LoRa module,
 * it proceeds to handle the reception of the LoRa packet.
 * 
 * @param GPIO_Pin GPIO pin that triggered the interrupt.
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
#ifdef __cplusplus
}
#endif

#endif /* __CFG_GPIO_EXTI_H */