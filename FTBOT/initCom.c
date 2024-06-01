
#include "common.h"
#include "wifi_config.h"
#include <stdint.h>

#define MAX_RETRY 6
#define BUFFER_SIZE 128

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;
extern osEventFlagsId_t EFlagId_ObjInMsgQ;

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

uint8_t protobuf_init()
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
			return -1;
		}
	}
	return 1;
}

uint8_t uart_init()
{
	static const char command[] = "AT\r\n";
	if (HAL_UART_Transmit(&wifi_uart_nix, (uint8_t *)command, sizeof(command) - 1, 1000) != HAL_OK)
	{
		return 2; // Error
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

uint8_t wifi_init()
{
	static const char udpCommand[] = "AT+CIPSTART=\"UDP\",\"%s\",55719,58361,0\r\n";

	static char commandBuffer[128];
	snprintf(commandBuffer, sizeof(commandBuffer), udpCommand, IP_ADDRESS_CONTROL); //ip address from control, from where? 

	HAL_UART_Transmit(&wifi_uart_nix, (uint8_t *)commandBuffer, sizeof(commandBuffer) - 1, 1000);

	osEventFlagsWait(EFlagId_ObjInMsgQ, 0x00000001U, osFlagsWaitAny, osWaitForever);

	static uint8_t buffer_msgQ[BUFFER_SIZE];
	size_t buffer_index = 0;
	uint8_t msg;
	
	while (osMessageQueueGetCount(MsgQId_nix) > 0)
	{
		osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
		buffer_msgQ[buffer_index++] = msg;
	

		if (msg == 'A') //CONNECTED / ALREADY CONNECTED how to check?
		{
			osMessageQueueGet(MsgQId_nix, &msg, NULL, 0);
			buffer_msgQ[buffer_index++] = msg;
			if (msg == 'L')
			{
				return 0; // OK
			}
		}
	}
	
	// All CONFIG AT Commands
	return 1;
}
