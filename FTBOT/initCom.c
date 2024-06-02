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

#include "initCom.h"
#include "wifi_config.h"

#define BUFFER_SIZE 128

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;
extern osEventFlagsId_t EFlagId_ObjInMsgQ;

/**
 *  @brief Check if file exists
 *  @details Uses fopen to check if file exists
 *  @retval bool : true if file exists, false otherwise
 */
bool file_exists(const char *filename)
{
	FILE *file = fopen(filename, "r"); // error why?
	if (file)
	{
		fclose(file);
		return true;
	}
	return false;
}

/**
 *  @brief Initialisation of the nanopb parser
 *  @details Checks if all required files are there for the parser, uses file_exists
 *  @retval int8_t : 0 if all files are there, 1 otherwise
 */
int8_t protobuf_init()
{
	static const char *required_files[] = {
		"../PB/ftbot.pb.c",
		"../PB/pb_common.c",
		"../PB/pb_decode.c",
		"../PB/pb_encode.c",
	};

	for (size_t i = 0; i < sizeof(required_files) / sizeof(required_files[0]); i++)
	{
		if (!file_exists(required_files[i]))
		{
			return 1;
		}
	}
	return 0; // OK
}

/**
 *  @brief Check of the UART connection
 *  @details Sends an AT command to the ESP01 module to check if the connection is established
 *  @retval int8_t : 0 if OK, 1 if not OK, 2 if HAL error
 */
int8_t uart_init()
{
	static const char command[] = "AT\r\n";
	if (HAL_UART_Transmit(&wifi_uart_nix, (uint8_t *)command, sizeof(command) - 1, 1000) != HAL_OK)
	{
		return 2;
	}

	osEventFlagsWait(EFlagId_ObjInMsgQ, 0x00000001U, osFlagsWaitAny, osWaitForever);

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
	snprintf(commandBuffer, sizeof(commandBuffer), udpCommand, IP_ADDRESS_CONTROL); // TODO: ip address from control, from where?

	HAL_UART_Transmit(&wifi_uart_nix, (uint8_t *)commandBuffer, sizeof(commandBuffer) - 1, 1000);

	osEventFlagsWait(EFlagId_ObjInMsgQ, 0x00000001U, osFlagsWaitAny, osWaitForever);

	static uint8_t buffer_msgQ[BUFFER_SIZE];
	size_t buffer_index = 0;

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
