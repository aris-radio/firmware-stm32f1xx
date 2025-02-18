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
 * @file    main.c
 * @brief   Main program body for ARIS Radio
 * @author  
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* (Add any typedefs or structs you want to expose here) */

/* Exported constants --------------------------------------------------------*/
/* (Define any project-level constants here) */

/* Exported macro ------------------------------------------------------------*/
/* (Define any macro utilities here) */

/* Exported functions ------------------------------------------------------- */
/**
 * @brief  Main program entry point
 * @param  None
 * @retval int
 */
int main(void);

/**
 * @brief  Configures the system clock.
 *         Settings:
 *           - System Clock source         = PLL (HSE)
 *           - SYSCLK(Hz)                  = 72000000
 *           - HCLK(Hz)                    = 72000000
 *           - AHB Prescaler               = 1
 *           - APB1 Prescaler              = 2
 *           - APB2 Prescaler              = 1
 *           - HSE Frequency(Hz)           = 8000000
 *           - HSE PREDIV1                 = 1
 *           - PLLMUL                      = 9
 *           - Flash Latency(WS)           = 2
 * @param  None
 * @retval None
 */
void SystemClock_Config(void);

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the file name and the line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: line number of the assert_param error
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line);
#endif

/**
 * @brief  This function is executed in case of an error occurrence.
 *         It is declared static by default (file scope).
 * @param  None
 * @retval None
 */
static void Error_Handler(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/ 
