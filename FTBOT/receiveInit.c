#include "common.h"

#define BUFFER_SIZE 1

void RxHalfCpltCallback(UART_HandleTypeDef *huart);
void RxCpltCallback(UART_HandleTypeDef *huart);

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;

uint8_t buffer_msgQ[BUFFER_SIZE] __attribute__((section("ETTI4dmaVar")));

void receive_init()
{
	HAL_UART_RegisterCallback(&wifi_uart_nix, HAL_UART_RX_HALFCOMPLETE_CB_ID, RxHalfCpltCallback);
	HAL_UART_RegisterCallback(&wifi_uart_nix, HAL_UART_RX_COMPLETE_CB_ID, RxCpltCallback);
	
  HAL_UART_Receive_DMA(&wifi_uart_nix, buffer_msgQ, BUFFER_SIZE);
}

void RxHalfCpltCallback(UART_HandleTypeDef *huart) 
{
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}

void RxCpltCallback(UART_HandleTypeDef *huart) 
{
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}