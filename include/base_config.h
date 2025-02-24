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
 * @file    base_config.h
 * @brief   Base configuration for ARIS Radio
 * @author  ARIS Alliance
 *
 */

#ifndef __BASE_CONFIG_H
#define __BASE_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* __BASE_CONFIG_H */