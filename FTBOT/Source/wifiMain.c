/**
 *******************************************************************************
 * @file      wifiMain.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Main thread for Initialisation and start of other threads
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"

osMutexId_t driveControlMutId;

osMessageQueueId_t MsgQId_nix;

driveInfo_t driveInfo; // Drive information variable - MODEL

E4disp_t driveDisp = {.defaultSetting = true};

/**
 *  @brief Main thread for initialise parser and configure UART and wifi, and start other threads and printout
 *  @details Initialisation:
 * 				- Nanopb parser (check if all files are there)
 * 				- UART (checks if connection to ESP01 is established)
 * 				- Wifi (creates socket)
 * 			 Start other threads (transmit, receive, drive)
 * 			 Printout to serial debug USB
 *  @param  [in] arg : Pointer to argument (not used)
 */

__NO_RETURN void mainThread(void *arg)
{
	int8_t init_return = 0;
	driveInfo_t drive_local;
	driveControlMutId = osMutexNew(NULL);
	E4ftbotTerminalInit(&driveDisp);

	MsgQId_nix = osMessageQueueNew(128, sizeof(uint8_t), NULL);
	receive_init();

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

	case 2:
		printf("Wifi socket initialization successful: Socket has already been created.\n");
	}

	osThreadNew(transmitThread, NULL, NULL);
	osThreadNew(receiveThread, NULL, NULL);
	osThreadNew(driveThread, NULL, NULL);

	printf("-------------------------------------------\n"
		   "            Drive Wifi program\n"
		   "===========================================\n"
		   "         Side :  Left       | Right \n"
		   "-------------------------------------------\n");

	osThreadSetPriority(osThreadGetId(), osPriorityNormal);

	for (;;)
	{
		// Copy the values of the global variable to a local variable
		// under the protection of a mutex
		osMutexAcquire(driveControlMutId, osWaitForever);
		driveInfo.currSpeedL = motGetCurrSpeed(leftMotSel);
		driveInfo.currSpeedR = motGetCurrSpeed(rightMotSel);
		osMutexRelease(driveControlMutId);
		
		osMutexAcquire(driveControlMutId, osWaitForever);
		drive_local = driveInfo;
		osMutexRelease(driveControlMutId);

		// Add function to set Cursor to the begin of data section
		E4setPosDisp(&driveDisp, 6, 0);

		// Printout to serial debug USB
		printf("measured speed:  %+6.3f m/s |  %+6.3f m/s\n"
			   "voltage:	 %+6.3f V\n",
			   drive_local.currSpeedL, drive_local.currSpeedR,
			   drive_local.voltage);

		osDelay(200);
	}
}
