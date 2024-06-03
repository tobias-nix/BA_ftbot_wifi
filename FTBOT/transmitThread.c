/**
 *******************************************************************************
 * @file      transmitThread.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Thread to transmit data via UART
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "transmitThread.h"

typedef struct
{
  float nomSpeedL;  /*!< new nominal speed left */
  float nomSpeedR;  /*!< new nominal  speed right */
  float currSpeedL; /*!< current speed left */
  float currSpeedR; /*!< current speed right */
  uint32_t voltage; /*!< TODO: to test set by hex SW1 */
} driveInfo_t;      /*!< Data type to store data for drive information  */

extern UART_HandleTypeDef wifi_uart_nix;
extern osMutexId_t driveControlMutId;
extern driveInfo_t driveInfo;

osThreadId_t transmitId;
osSemaphoreId_t uartTxSemaphore;                            // Semaphore for UART transmission
uint16_t buffer_transmit[128] __attribute__((aligned(32))); // Buffer for the transmission of AT command

/**
 *  @brief Thread to transmit data via UART
 *  @details Transmits the robot status via UART
 *           In the <b>super loop</b> the following steps are executed:
 *           1. Get the current speed of the left and right motor
 *           2. Get the current voltage, with the help of a mutex
 *           3. Encode the robot status
 *           4. Send the AT send command with the length of the message
 *           5. Send the message
 *           6. Delay for 200ms
 *  @param  [in] argument : Pointer to argument (not used)
 */
__NO_RETURN void transmitThread(void *argument)
{
  transmitId = osThreadGetId();
  osThreadSetPriority(transmitId, osPriorityNormal);

  static uint8_t buffer_stream[128]; // Buffer for the parsed protobuf message

  uartTxSemaphore = osSemaphoreNew(1U, 1U, NULL);
  if (uartTxSemaphore == NULL)
  {
    // Error Handling
  }

  ftbot_RobotStatus robotStatus = ftbot_RobotStatus_init_zero;
  while (1)
  {
    robotStatus.true_left_speed = motGetCurrSpeed(leftMotSel);
    robotStatus.true_right_speed = motGetCurrSpeed(rightMotSel);

    if (osMutexAcquire(driveControlMutId, 500) == osOK)
    {
      int32_t rawVoltage = getBatteryVoltageRaw(); // Retrieves the battery level, with polling
		driveInfo.voltage = calcPotiRaw2Volt(rawVoltage); // TODO: dot number not correct
      robotStatus.voltage = driveInfo.voltage;
    }
    osMutexRelease(driveControlMutId);

    pb_ostream_t stream = pb_ostream_from_buffer(buffer_stream, sizeof(buffer_stream));

    if (!pb_encode(&stream, ftbot_RobotStatus_fields, &robotStatus)) // Encode the robot status with the nanopb parser
    {
      // Error handling
    }
    SCB_InvalidateDCache_by_Addr(buffer_transmit, sizeof(buffer_transmit));
    int commandLength = snprintf((char *)buffer_transmit, sizeof(buffer_transmit), "AT+CIPSEND=%d\r\n", stream.bytes_written);

    if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK)
    {
      HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t *)buffer_transmit, commandLength); // Send the AT send command
    }
    SCB_CleanDCache_by_Addr(buffer_transmit, sizeof(buffer_transmit));
    if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK)
    {
      HAL_UART_Transmit_DMA(&wifi_uart_nix, buffer_stream, stream.bytes_written); // Send the message
    }
    osDelay(200);
  }
}

/**
 *  @brief Callback function for the UART transmission
 *  @details Callback function for the UART transmission
 *           Releases the UART transmission semaphore
 *  @param  [in] huart : Pointer to the UART handle
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  osSemaphoreRelease(uartTxSemaphore);
}