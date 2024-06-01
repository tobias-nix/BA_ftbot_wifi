#include "common.h"
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern UART_HandleTypeDef wifi_uart_nix;

extern ftbotMotor_t leftMotorDescriptor;
extern ftbotMotor_t rightMotorDescriptor;
extern float motGetCurrSpeed(motSel_t motSel);

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

  ftbot_RobotStatus robotStatus = ftbot_RobotStatus_init_zero;
  robotStatus.true_left_speed = motGetCurrSpeed(leftMotSel);
  robotStatus.true_right_speed = motGetCurrSpeed(rightMotSel);
  robotStatus.voltage = 12.0; // Assumption that the voltage is constant, only for testing

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