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
 * @file    cfg_gpio_exti.c
 * @brief   Interruption functions for GPIO pins.
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "stm32f1xx_hal.h"
#include "cfg_spi1_define.h"

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(SPI1_DIO0_PIN);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == SPI1_DIO0_PIN) // DIO0 pin LoRa
    {
        // Aquí atendemos la interrupción de LoRa (RxDone).
        // 1) Leer los flags de IRQ en el módulo LoRa
        // 2) Verificar qué bandera se activó (RxDone, etc.)
        // 3) Leer el payload si es necesario
        // 4) Limpiar los flags de interrupción en el LoRa
    }
}

/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/