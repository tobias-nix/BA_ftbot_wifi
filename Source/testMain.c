// Comment

#include "test_at.h"

__NO_RETURN void blueLedThread(void * arg);
__NO_RETURN void sendAtThread(void * arg);

__NO_RETURN void mainThread(void * arg)
{
  osThreadNew(blueLedThread, NULL, NULL);
  osThreadNew(sendAtThread, NULL, NULL);
}

__NO_RETURN void blueLedThread(void * arg)
{
  setBlueLedIntervall();
}

__NO_RETURN void sendAtThread(void * arg){
  sendAt();
}