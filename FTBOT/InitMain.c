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
#include "receive.h"
#include "msgQFlagThread.h"
#include "driveThread.h"
#include "ftbotTerminal.h"              // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotLedSWBumper.h"           // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

#define TFLG_CONTROL_START  0x00000001 /*!< Thread Flag to start control loop */

osTimerId_t timer_id;
osMutexId_t driveControlMutId;
osThreadId_t control_id;

/** @brief data type to store data for drive information  */
typedef struct {
  float nomSpeedL;  /*!< new nominal speed left */
  float nomSpeedR;  /*!< new nominal  speed right */
  float currSpeedL; /*!< current speed left */
  float currSpeedR; /*!< current speed right */
} driveInfo_t; /*!< Data type to store data for drive information  */


driveInfo_t driveInfo; /*!< Drive information variable */

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
	int8_t init_return = 0;
	driveInfo_t drive_local;
  driveControlMutId = osMutexNew(NULL);
	E4ftbotTerminalInit(&driveDisp);  
	
  MsgQId_nix = osMessageQueueNew(128, sizeof(uint8_t), NULL);
	receive_init();
	
	EFlagId_ObjInMsgQ = osEventFlagsNew(NULL);
	
	osThreadNew(msgQFlagThread, NULL, NULL);
	
	init_return = uart_init();
	switch (init_return)
	{
		case 0:
			printf("UART initialization successful.\n");
			break;
		
		case 1:
      printf("UART initialization failed: No successful response from esp01.\n");
			break;
		
		case 2:
      printf("UART initialization failed: UART connection could not be established.\n");
			break;
	}
	
	init_return = wifi_init();
	switch (init_return)
	{
		case 0:
			printf("Wifi socket initialization successful.\n");
			break;
		
		case 1:
      printf("Wifi socket initialization failed: Socket could not created.\n");
			break;
	}
	
	
  // osThreadNew(transmitThread, NULL, NULL);
	osThreadNew(receiveThread, NULL, NULL);
	osThreadNew(driveThread, NULL, NULL);
  
	printf("-------------------------------------------\n"
         "            Drive Wifi program\n"
         "===========================================\n"
         "         Side :  Left       | Right \n"
         "-------------------------------------------\n");

  for(;;){		
		
    // Copy the values of the global variable to a local variable 
    // under the protection of a mutex
    osMutexAcquire(driveControlMutId, osWaitForever);
    drive_local = driveInfo;
    osMutexRelease(driveControlMutId);
		
    // Add function to set Cursor to the begin of data section
    E4setPosDisp(&driveDisp, 5,0);
    
    // Replace the constant values with the values from loval variable
    printf("nominal speed:   %+6.3f m/s |  %+6.3f m/s\n"
           "measured speed:  %+6.3f m/s |  %+6.3f m/s\n",
           drive_local.nomSpeedL, drive_local.nomSpeedR,
           drive_local.currSpeedL, drive_local.currSpeedR);
		
    osDelay(200);
  }
}


