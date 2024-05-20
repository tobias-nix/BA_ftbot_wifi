
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern CRC_HandleTypeDef hcrc;
/**
  * @addtogroup DRIVECRCFUNC 
  * @{
  */


/**
  * @brief Function to calculate 16 bit CRC code from message
  * @details This function calculates the 16-bit CRC code required for 
  *          data exchange with the drive motors.
  * @param [in] pMsg : Pointer to the message array
  * @param      size : Number of bytes used for the calculation of the CRC code.
  * @retval "CRC Code" : 16 bit CRC code
  */  
uint32_t driveCalcCRC(uint8_t * pMsg, uint32_t size)
{
  return HAL_CRC_Calculate(&hcrc, (uint32_t*) pMsg, size);
}