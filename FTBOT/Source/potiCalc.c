/**
 *******************************************************************************
 * @file      potiCalc.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      23.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Function to calculate voltage from ADC raw value
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"

/**
 * @brief Function calculates voltage from adc raw value
 * @details The voltage is calculated from ADC raw value
 * @param potiRaw : ADC raw value (0 - 4095)
 * @retval voltage in [V] (0V - 12.0V)
 */
float calcPotiRaw2Volt(int32_t potiRaw)
{
  return (12.0f / 4095.0f) * potiRaw;
}
