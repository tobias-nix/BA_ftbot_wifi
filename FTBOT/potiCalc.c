
#include "transmitThread.h"

/**
  * @brief Function calculates voltage from adc raw value
  * @details The voltage is calculated from ADC raw value
  * @param potiRaw : ADC raw value (0 - 4095)
  * @retval voltage in [V] (0V - 12.0V)
  */
float calcPotiRaw2Volt(int32_t potiRaw)
{
	float tmp = (float) potiRaw;
	float tmp2 = 12.0f / 4095.0f;
	float tmp3 = tmp2 * tmp;
	return tmp3;
}
