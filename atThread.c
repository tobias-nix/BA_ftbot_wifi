// Comment

#include "test_at.h"

char rx_buffer[150];
extern UART_HandleTypeDef huart6;

void sendAt()
{
  setRedLed(true);
  osDelay(100);
  setRedLed(false);
  uint8_t at_command[] = "AT+GMR\r\n";
  memset(rx_buffer, 0, sizeof(rx_buffer));
  HAL_UART_Transmit(&huart6, at_command, sizeof(at_command)-1, 100);
  HAL_StatusTypeDef result = HAL_UART_Receive(&huart6, (uint8_t *)rx_buffer, sizeof(rx_buffer) - 1, 5000);

    if (result == HAL_OK) {
        if (strstr(rx_buffer, "OK") != NULL) {
          setRedLed(true);
          osDelay(1000);
        } else if (result == HAL_TIMEOUT) {
          HAL_UART_Transmit(&huart6, at_command, sizeof(at_command)-1, 100);
        } else {
          
        }
     }
}