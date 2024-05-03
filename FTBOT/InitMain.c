/**
  ******************************************************************************
  * @file      InitMain.c
  * @author    Tobias Nix
  * @version   V1.0.0
  * @date      12.04.2024
  * @copyright 
  * @brief  Program to initialise parser and configure UART and wifi and to
            send data to pc
  ******************************************************************************
  * @par Change Log:    
  *  @details V1.0.0 Tobias Nix
  *           - Initial version
  ******************************************************************************
  */

#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "wifi_config.h"
#include <stdio.h>

/**
  * @brief Main thread for initialise parser and configure UART and wifi
  * @details This is the thread which starts after power on
  *          Init parser
  *          - checks if all files are there
  *          Configure serial connection
  *          - configure UART (baudrate, ...)
  *          Configure ESP01 "wifi"
  *          - takes selected name and creates ip
  *          - creates udp socket
  *          - generates connection to pc
  *          - tests connection
  *          Start next threads
  *          - reciving thread
  *          - drive thread
  *          - at thread
  * @param  [in] arg : Pointer to argument (not used)
  */ 

typedef struct {
  uint32_t  baudrate;
  uint8_t   databits;
  uint8_t   stopbits;
  uint8_t   parity;
  uint8_t   flow_control;
} COM_UART_INTERFACE;

  // Initialize Protobuf parser
void protobuf_init() {
    // Your initialization code here
}

// Initialize UART communication with ESP-01
void uart_init() {
  COM_UART_INTERFACE com;
  
  com.baudrate = 115200;
  com.databits =
  com.stopbits =
  com.parity = 
  com.flow_control = 
    // Your initialization code here
}

// Initialize ESP-01 WiFi module
void wifi_init() {
    // Your initialization code here
}

// Receiving thread function
void receivingThread(void *argument) {
    while (1) {
        // Receive data and process
    }
}

// Drive thread function
void driveThread(void *argument) {
    while (1) {
        // Control motor or drive
    }
}

// AT command thread function
void atThread(void *argument) {
    while (1) {
        // Send AT commands to ESP-01
    }
}

__NO_RETURN void mainThread(void * arg)
{
  char *ip = IP_ADDRESS;
  
  HAL_Init();
  osKernelInitialize();
  
  protobuf_init();
  uart_init();
  wifi_init();
  
  // Start receiving thread
  osThreadNew(receivingThread, NULL, NULL);

  // Start drive thread
  osThreadNew(driveThread, NULL, NULL);

  // Start AT command thread
  osThreadNew(atThread, NULL, NULL);

  // Start scheduler
  osKernelStart();
  
  for(;;) {
    
  }
}

