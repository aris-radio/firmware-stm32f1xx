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
 * @file    main.h
 * @brief   Main program body for ARIS Radio
 * @author  ARIS Alliance
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "cfg_gpio_define.h"
#include "cfg_spi1_define.h"
#include "base_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief  Main program entry point
 * @param  None
 * @retval int
 */
int main(void);
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

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* Initialize the STM32F1 HAL library */
    HAL_Init();

    /* Configure the system clock to 64 MHz (example) */
    SystemClock_Config();

    /* Initialize GPIO and SPI */
    MX_GPIO_Init();
    MX_SPI1_Init();

    /*
       At this point, SPI is ready to communicate with the RF96 module.

       Important: remember that additional pins on the RFM96 might need
       initialization, for example:
         - RST (Reset pin), usually controlled by a GPIO line
         - DIO0, DIO1, etc. (interrupt/status lines)
       Make sure to configure these pins according to your project needs.
    */
    while (1)
    {
        /* Toggle PC13 every 50 ms */
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(50);
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
    while (1)
    {
    }
}
#endif /* USE_FULL_ASSERT */


 


/************************ (C) COPYRIGHT ARIS Alliance *****END OF FILE****/ 