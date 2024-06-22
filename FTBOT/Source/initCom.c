/**
 *******************************************************************************
 * @file      initCom.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Initialisation of the parser & communication module
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"
#include "wifiConfig.h"

#define BUFFER_SIZE 128

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;

/**
 *  @brief Check of the UART connection
 *  @details Sends an AT command to the ESP01 module to check if the connection is established
 *  @retval int8_t : 0 if OK, 1 if not OK, 2 if HAL error
 */
int8_t uart_init()
{
	static const char command[] = "AT\r\n";
	
	for (int i = 0; i < 3; i++)
	{
		if (HAL_UART_Transmit(&wifi_uart_nix, (uint8_t *)command, sizeof(command) - 1, osWaitForever) != HAL_OK)
		{
			return 2;
		}
		osDelay(20);
	}

	static uint8_t buffer_msgQ[BUFFER_SIZE];
	int8_t buffer_index = 0;

	while (osMessageQueueGetCount(MsgQId_nix) > 0)
	{
		uint8_t msg;
		osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
		buffer_msgQ[buffer_index++] = msg;

		if (msg == 'O')
		{
			osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
			buffer_msgQ[buffer_index++] = msg;
			if (msg == 'K')
			{
				osMessageQueueReset(MsgQId_nix);
				return 0; // OK
			}
		}
	}
	return 1;
}

/**
 *  @brief Initialisation of the wifi connection
 *  @details Sends an AT command to the ESP01 module to create a socket
 *  @retval int8_t : 0 if OK, 1 if not OK, 2 if already connected
 */
int8_t wifi_init()
{
	static const char udpCommand[] = "AT+CIPSTART=\"UDP\",\"%s\",55719,58361,0\r\n";

	static char commandBuffer[128];
	snprintf(commandBuffer, sizeof(commandBuffer), udpCommand, IP_ADDRESS_CONTROL);
	// wenn nicht anders möglich in wifiConfig.h festlegen
	HAL_UART_Transmit(&wifi_uart_nix, (uint8_t *)commandBuffer, sizeof(commandBuffer) - 1, 1000);

	static uint8_t buffer_msgQ[BUFFER_SIZE];
	size_t buffer_index = 0;
	
	osDelay(20);

	while (osMessageQueueGetCount(MsgQId_nix) > 0)
	{
		uint8_t msg;
		osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
		buffer_msgQ[buffer_index++] = msg;

		if (msg == 'O')
		{
			osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
			buffer_msgQ[buffer_index++] = msg;
			if (msg == 'K')
			{
				return 0; // OK
			}
		}
		else if (msg == 'A')
		{
			osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
			buffer_msgQ[buffer_index++] = msg;
			if (msg == 'L')
			{
				return 2; // OK
			}
		}
	}
	return 1;
}
