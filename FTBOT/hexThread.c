/**
 *******************************************************************************
 * @file      hexThread.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Function to read the hex value from the switch
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "transmitThread.h"

/**
 * @brief  Read the hex value from the switch
 * @param  None
 * @retval uint32_t: The hex value
 */
uint32_t readHex()
{
  uint32_t tmp = 0;
  uint32_t result;
  tmp = GPIOF->IDR; // TODO: SW1 in Cube MX

  result = ((~tmp >> 4) & 0xF);
  return (result); // TODO: retval should be the decimal value of the switch, 0-15
}
