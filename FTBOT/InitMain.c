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

//#include "cmsis_os2.h"     // ::CMSIS:RTOS2
//#include "stm32f7xx_hal.h" // Keil::Device:STM32Cube HAL:Common
//#include "wifi_config.h"
//#include "main.h"
//#include "ftbot.pb.h"
//#include "transmitThread.c"
//#include <stdio.h>
//#include <string.h>
//#include <pb_encode.h>

#include "common.h"
#include "initCom.h"
#include "transmitThread.h"
#include "receiveThread.h"
#include "msgQFlagThread.h"
#include "ftbotTerminal.h"              // ETTI4 FTbot:EmbSysLab:FTbotLib

E4disp_t driveDisp = {.defaultSetting = true};

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

osMessageQueueId_t MsgQId_nix;
osEventFlagsId_t EFlagId_ObjInMsgQ;


__NO_RETURN void mainThread(void *arg)
{
	//protobuf_init(); //debugg: fopen not functionabel
	
	E4ftbotTerminalInit(&driveDisp);  
  
  printf("Hello \r\n");
	
  MsgQId_nix = osMessageQueueNew(128, sizeof(uint8_t), NULL);
  osThreadNew(receiveThread, NULL, NULL);
	
	EFlagId_ObjInMsgQ = osEventFlagsNew(NULL);
	
	osThreadNew(msgQFlagThread, NULL, NULL);
	uart_init(); //Error handling
	
	wifi_init(); //Error handling
	
	
  osThreadNew(transmitThread, NULL, NULL);
  

  for (;;)
  {
    // Main thread loop
//    osDelay(osWaitForever);
    
    printf("Hello \r\n");
    osDelay(500);
  }
}


