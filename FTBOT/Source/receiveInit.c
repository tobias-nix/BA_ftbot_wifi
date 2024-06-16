/**
 *******************************************************************************
 * @file      receiveInit.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Function to initialize the dma and callbacks for the receive
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "receive.h"

#define BUFFER_SIZE 1 // TODO: DMA output is not correct with buffer 2

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;

uint8_t buffer_msgQ[BUFFER_SIZE] __attribute__((section("ETTI4dmaVar"))); // buffer in a unchached memory area for dma, see: @ref e4EmbSys746.sct

/**
 *  @brief Receive initialization
 *  @details Registers the callbacks for the receive
 *           and starts the receive dma
 */
void receive_init()
{
  HAL_UART_RegisterCallback(&wifi_uart_nix, HAL_UART_RX_HALFCOMPLETE_CB_ID, RxHalfCpltCallback);
  HAL_UART_RegisterCallback(&wifi_uart_nix, HAL_UART_RX_COMPLETE_CB_ID, RxCpltCallback);

  HAL_UART_Receive_DMA(&wifi_uart_nix, buffer_msgQ, BUFFER_SIZE);
}

/**
 *  @brief Callback for half complete receive
 *  @details Puts the message in the message queue
 */
void RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}

/**
 *  @brief Callback for complete receive
 *  @details Puts the message in the message queue
 */
void RxCpltCallback(UART_HandleTypeDef *huart)
{
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}