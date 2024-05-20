#include "common.h"

extern UART_HandleTypeDef wifi_uart_nix;

osSemaphoreId_t uartTxSemaphore;
uint16_t buffer_transmit[128] __attribute__((aligned(32)));

void transmitThread(void *argument)
{
  static uint8_t buffer_stream[128];

  uartTxSemaphore = osSemaphoreNew(1U, 1U, NULL);
  if (uartTxSemaphore == NULL)
  {
    // Error Handling
    return;
  }

  static const char udpCommand[] = "AT+CIPSTART=\"UDP\",\"192.168.10.2\",55719,58361,0\r\n";
  if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK)
  {
    HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t *)udpCommand, sizeof(udpCommand) - 1); // Exclude null terminator
  }

  ftbot_RobotStatus robotStatus = ftbot_RobotStatus_init_zero;
  robotStatus.true_left_speed = 3.0;
  robotStatus.true_right_speed = 5.0;
  robotStatus.voltage = 12.0;

  pb_ostream_t stream = pb_ostream_from_buffer(buffer_stream, sizeof(buffer_stream));

  if (!pb_encode(&stream, ftbot_RobotStatus_fields, &robotStatus))
  {
    // Error handling
    return;
  }

  while (1)
  {
    SCB_InvalidateDCache_by_Addr(buffer_transmit, sizeof(buffer_transmit));
    int commandLength = snprintf((char *)buffer_transmit, sizeof(buffer_transmit), "AT+CIPSEND=%d\r\n", stream.bytes_written);

    if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK)
    {
      HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t *)buffer_transmit, commandLength);
    }
    SCB_CleanDCache_by_Addr(buffer_transmit, sizeof(buffer_transmit));
    if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK)
    {
      HAL_UART_Transmit_DMA(&wifi_uart_nix, buffer_stream, stream.bytes_written);
    }
    osDelay(200);
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  osSemaphoreRelease(uartTxSemaphore);
}