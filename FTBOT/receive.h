
#include "common.h"

void receiveThread(void *arg);
void receive_init();
void RxHalfCpltCallback(UART_HandleTypeDef *huart);
void RxCpltCallback(UART_HandleTypeDef *huart);