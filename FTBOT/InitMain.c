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

__NO_RETURN void mainThread(void * arg)
{
  char *ip = IP_ADDRESS;
}

