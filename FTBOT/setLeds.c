// Comment

#include "test_at.h"

void setBlueLedIntervall()
{
  for(;;)
  {
    HAL_GPIO_TogglePin(blueLed_GPIO_Port, blueLed_Pin);
    osDelay(500);
  }
}

void setRedLed(bool onoff)
{
	GPIO_PinState pinState;
	
	if (onoff) {
		pinState = GPIO_PIN_SET;
	} else {
		pinState = GPIO_PIN_RESET;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, pinState);
	return;
}
