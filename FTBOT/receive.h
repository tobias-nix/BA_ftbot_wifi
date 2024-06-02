/**
 *******************************************************************************
 * @file      receive.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Header file for the receive thread
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"
#include "ftbotDrive.h" // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

void receiveThread(void *arg);
void receive_init();
void RxHalfCpltCallback(UART_HandleTypeDef *huart);
void RxCpltCallback(UART_HandleTypeDef *huart);
void processReceivedData(uint8_t *data, size_t length);
void convertSpeedSteeringToWheelSpeeds(float speed, float steering, float *leftSpeed, float *rightSpeed);