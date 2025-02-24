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
 * @file    cfg_gpio_define.c
 * @brief   Config the gpio pins for the stm32f1xx
 * @author  ARIS Alliance
 */

#ifndef __CFG_GPIO_DEFINE_H
#define __CFG_GPIO_DEFINE_H


#ifdef __cplusplus
extern "C"
{
#endif

/**
  * @brief  Initializes the GPIO pins needed for SPI1 and an optional LED pin.
  *         - Configures PA4 as NSS (manual output)
  *         - Configures PA5 as SCK, PA6 as MISO, PA7 as MOSI
  *         - Configures PC13 as output for LED (optional)
  * @retval None
  */
void MX_GPIO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __CFG_GPIO_DEFINE_H */