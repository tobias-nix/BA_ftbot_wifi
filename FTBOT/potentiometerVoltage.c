
#include "transmitThread.h"

extern ADC_HandleTypeDef hadc1;

/**
  * @brief Function to read raw supply voltage
  * @details The function reads the raw values of the supply voltage. 
  *          Polling is used for this. The function returns the read value. 
  *          If no result is available within 10 ms, the function returns -1.
  * @retval Result : can be
  *                  @arg measured value (0 - 4095)
  *                  @arg -1 in case of timeout
  */
int32_t getBatteryVoltageRaw(void)
{
    if (HAL_ADC_Start(&hadc1) ==  HAL_OK) {
      if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
       return HAL_ADC_GetValue(&hadc1);
     }
   }
   return -1;
}