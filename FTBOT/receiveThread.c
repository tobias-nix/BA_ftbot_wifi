#include "common.h"

#define BUFFER_SIZE 2

void RxHalfCpltCallback(UART_HandleTypeDef *huart);
void RxCpltCallback(UART_HandleTypeDef *huart);

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;

osMutexId_t msgQueueMutex;

uint8_t buffer_msgQ[BUFFER_SIZE] __attribute__((section("ETTI4dmaVar")));

uint8_t half_counter = 0;
uint8_t cplt_counter = 0;

/**
 *  @brief Brief description
 *  @details More details
 *  @param [in] argument Description for argument
 *  @return Return description
 */
void receiveThread(void *argument)
{
	msgQueueMutex = osMutexNew(NULL);
	HAL_UART_RegisterCallback(&wifi_uart_nix, HAL_UART_RX_HALFCOMPLETE_CB_ID, RxHalfCpltCallback);
	HAL_UART_RegisterCallback(&wifi_uart_nix, HAL_UART_RX_COMPLETE_CB_ID, RxCpltCallback);
	
  HAL_UART_Receive_DMA(&wifi_uart_nix, buffer_msgQ, BUFFER_SIZE);
}

void RxHalfCpltCallback(UART_HandleTypeDef *huart) 
{
	half_counter++;
//  SCB_InvalidateDCache_by_Addr(buffer_msgQ, sizeof(buffer_msgQ));
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}

void RxCpltCallback(UART_HandleTypeDef *huart) 
{
	cplt_counter++;
//  SCB_InvalidateDCache_by_Addr(buffer_msgQ, sizeof(buffer_msgQ));
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}