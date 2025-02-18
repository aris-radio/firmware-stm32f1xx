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
 * @file    main.c
 * @brief   Main program body for ARIS Radio
 * @author  
 * @date    
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F1xx_HAL_Examples
 * @{
 */

/** @addtogroup Templates
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStruct;

/* Private function prototypes -----------------------------------------------*/
/* (Declared in main.h) */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /*
       STM32F103xB HAL library initialization:
       - Flash prefetch configuration
       - Systick timer is configured by default as the source for time base
         (used by HAL_Delay and other timing functions).
       - Set NVIC Group Priority to 4
       - Low Level Initialization
    */
    HAL_Init();

    /* Configure the system clock to 64 MHz (via PLL, see SystemClock_Config) */
    SystemClock_Config();

    /* Enable the clock for GPIOC (often used for onboard LED on PC13) */
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /*
       Configure PC13 as push-pull output with:
       - Pull-up
       - High speed
       - Output push-pull mode
    */
    GPIO_InitStruct.Pin   = GPIO_PIN_13;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Infinite loop */
    while (1)
    {
        /* Toggle PC13 (LED) every 200 ms */
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(50);
    }
}

/**
  * @brief  System Clock Configuration
  *         Configures HSE at 8 MHz and uses the PLL to achieve 64 MHz 
  *         (example with PLL x9 = 72 MHz or other custom settings).
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef clkinitstruct = {0};
    RCC_OscInitTypeDef oscinitstruct = {0};
    RCC_PeriphCLKInitTypeDef rccperiphclkinit = {0};

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    oscinitstruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;
    oscinitstruct.HSEState            = RCC_HSE_ON;
    oscinitstruct.HSEPredivValue      = RCC_HSE_PREDIV_DIV1;
    oscinitstruct.PLL.PLLMUL          = RCC_PLL_MUL9;
    oscinitstruct.PLL.PLLState        = RCC_PLL_ON;
    oscinitstruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;

    if (HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
    {
        /* Initialization error */
        Error_Handler();
    }

    /* Example: USB clock selection (48 MHz from PLL / 1.5) */
    rccperiphclkinit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    rccperiphclkinit.UsbClockSelection    = RCC_USBCLKSOURCE_PLL_DIV1_5;
    HAL_RCCEx_PeriphCLKConfig(&rccperiphclkinit);

    /* Configure the main clocks: SYSCLK, HCLK, PCLK1, PCLK2 */
    clkinitstruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    clkinitstruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clkinitstruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
    clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2) != HAL_OK)
    {
        /* Initialization error */
        Error_Handler();
    }
}

/**
  * @brief  This function is executed in case of an error occurrence.
  * @retval None
  */
static void Error_Handler(void)
{
    /* Add your own implementation to report the HAL error return state if needed */
    while (1)
    {
        /* Infinite loop */
    }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add custom implementation to report the file name and line number */
    while (1)
    {
    }
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/* COPYRIGHT ARIS Alliance */
