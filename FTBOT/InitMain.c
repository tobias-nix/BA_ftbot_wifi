/**
  ******************************************************************************
  * @file      InitMain.c
  * @author    Tobias Nix
  * @version   V1.0.0
  * @date      12.04.2024
  * @copyright
  * @brief  Program to initialise parser and configure UART and wifi and to
            send data to pc
  ******************************************************************************
  * @par Change Log:
  *  @details V1.0.0 Tobias Nix
  *           - Initial version
  ******************************************************************************
  */

#include "cmsis_os2.h"     // ::CMSIS:RTOS2
#include "stm32f7xx_hal.h" // Keil::Device:STM32Cube HAL:Common
#include "wifi_config.h"
#include "main.h"
#include "ftbot.pb.h"
#include <stdio.h>
#include <string.h>
#include <pb_encode.h>

/**
 * @brief Main thread for initialise parser and configure UART and wifi
 * @details This is the thread which starts after power on
 *          Init parser
 *          - checks if all files are there
 *          Configure serial connection
 *          - configure UART (baudrate, ...)
 *          Configure ESP01 "wifi"
 *          - takes selected name and creates ip
 *          - creates udp socket
 *          - generates connection to pc
 *          - tests connection
 *          Start next threads
 *          - reciving thread
 *          - drive thread
 *          - at thread
 * @param  [in] arg : Pointer to argument (not used)
 */

extern UART_HandleTypeDef wifi_uart_nix;

osSemaphoreId_t uartTxSemaphore;
uint16_t buffer_transmit[128] __attribute__((aligned(32)));

void transmitThread(void *argument)
{
  static uint8_t buffer_stream[128];

  uartTxSemaphore = osSemaphoreNew(1U, 1U, NULL);
  if (uartTxSemaphore == NULL)
  {
    // Handle error
    return;
  }

  static const char command[] = "AT\r\n";
  if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK)
  {
    HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t *)command, sizeof(command) - 1); // Exclude null terminator
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
    
    SCB_CleanDCache_by_Addr(buffer_transmit, sizeof(buffer_transmit));
    osDelay(200);
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  osSemaphoreRelease(uartTxSemaphore);
}

__NO_RETURN void mainThread(void *arg)
{
  // Create the transmit thread
  osThreadNew(transmitThread, NULL, NULL);

  for (;;)
  {
    // Main thread loop
  }
}
