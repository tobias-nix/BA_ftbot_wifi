/**
 *******************************************************************************
 * @file      transmitThread.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Header file for the transmit thread
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"
#include "ftbotDrive.h" // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

void transmitThread(void *argument);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
uint32_t readHex(void);
