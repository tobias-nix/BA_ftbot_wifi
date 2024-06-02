/**
 *******************************************************************************
 * @file      msgQFlagThread.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Thread to set flags for the message queue
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "msgQFlagThread.h"

extern osEventFlagsId_t EFlagId_ObjInMsgQ;
extern osMessageQueueId_t MsgQId_nix;

osThreadId_t msgQThreadId;

/**
 *  @brief Thread to set flags for the message queue
 *  @details Sets flag to signal if there is an object in the message queue
 *           Flag 0x00000001U if there is an object in the message queue
 *           Flag 0x00000002U if there is no object in the message queue
 *  @param  [in] argument : Pointer to argument (not used)
 */
__NO_RETURN void msgQFlagThread(void *argument)
{
	msgQThreadId = osThreadGetId();
	osThreadSetPriority(msgQThreadId, osPriorityNormal);

	while (1)
	{
		uint8_t count = osMessageQueueGetCount(MsgQId_nix);
		if (count > 0)
		{
			osEventFlagsSet(EFlagId_ObjInMsgQ, 0x00000001U); // > 0
		}
		else
		{
			osEventFlagsSet(EFlagId_ObjInMsgQ, 0x00000002U); // = 0
		}
	}
}