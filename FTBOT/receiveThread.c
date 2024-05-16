#include "common.h"

#define BUFFER_SIZE 2

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;

uint8_t buffer_msgQ[BUFFER_SIZE] __attribute__((aligned(32)));

void receiveThread(void *argument)
{
  while(1) {
    SCB_CleanDCache_by_Addr(buffer_msgQ, sizeof(buffer_msgQ));
    HAL_UART_Receive_DMA(&wifi_uart_nix, buffer_msgQ, BUFFER_SIZE);
    SCB_CleanDCache_by_Addr(buffer_msgQ, sizeof(buffer_msgQ));
  }
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart) 
{
  SCB_InvalidateDCache_by_Addr(buffer_msgQ, sizeof(buffer_msgQ));
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
  SCB_InvalidateDCache_by_Addr(buffer_msgQ, sizeof(buffer_msgQ));
  osMessageQueuePut(MsgQId_nix, &buffer_msgQ[0], 0, 0);
}