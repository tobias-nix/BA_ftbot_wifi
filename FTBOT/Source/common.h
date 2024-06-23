/**
 *******************************************************************************
 * @file      common.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      23.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Common header file for all source files
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmsis_os2.h" // ::CMSIS:RTOS2
#include "ftbot.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "stm32f7xx_hal.h" // Keil::Device:STM32Cube HAL:Common

#include "ftbotDrive.h"       // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotLedSWBumper.h" // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotTerminal.h"    // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

typedef struct
{
  float currSpeedL; /*!< current speed left */
  float currSpeedR; /*!< current speed right */
  float voltage;    /*!< current battery voltage */
} driveInfo_t;      /*!< Data type to store data for drive information  */

int8_t uart_init();
int8_t wifi_init();

void transmitThread(void *argument);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
int32_t getBatteryVoltageRaw(void);
float calcPotiRaw2Volt(int32_t potiRaw);

void receiveThread(void *arg);
void receive_init();
void RxHalfCpltCallback(UART_HandleTypeDef *huart);
void RxCpltCallback(UART_HandleTypeDef *huart);
void processReceivedData(uint8_t *data, size_t length);
void convertSpeedSteeringToWheelSpeeds(float speed, float steering, float *leftSpeed, float *rightSpeed);
void driveThread(void *arg);
#endif