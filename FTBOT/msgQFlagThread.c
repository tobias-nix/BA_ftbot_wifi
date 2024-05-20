
#include "common.h"

extern osEventFlagsId_t EFlagId_ObjInMsgQ;
extern osMessageQueueId_t MsgQId_nix;

void msgQFlagThread(void *argument)
{
	while (1) 
	{
		uint8_t count = osMessageQueueGetCount(MsgQId_nix);
		if (count > 0) 
		{
			osEventFlagsSet(EFlagId_ObjInMsgQ, 0x00000001U);
		}
	}
}