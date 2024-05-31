
#include "common.h"

void receiveThread(void *arg);
void receiveInit();
void RxHalfCpltCallback(UART_HandleTypeDef *huart);
void RxCpltCallback(UART_HandleTypeDef *huart);