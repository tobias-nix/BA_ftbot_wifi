
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include <stdbool.h>

bool file_exists(const char *filename);
uint8_t protobuf_init();
uint8_t uart_init();
uint8_t wifi_init();