
#include "common.h"
#include "ftbotDrive.h"

/**
  * @addtogroup DRIVETHREAD 
  * @{
  */

#define TFLG_DRIVE_START 0x00000001 /*!< Drive thread Flag for start loop */

osTimerId_t timerId;
osThreadId_t driveId;


/*! Description variable for left motor */
ftbotMotor_t leftMotorDescriptor = {
   .ID = 2,
   .nominalSpeed = 0.0,
   .currentSpeed = 0.0
};

/*! Description variable for right motor */
ftbotMotor_t rightMotorDescriptor = {
   .ID = 3,
   .nominalSpeed = 0.0,
   .currentSpeed = 0.0
};

/**
  * @brief Power fail variable
  * @details As soon as the supply voltage falls below a certain level, 
  * the variable is set to true.
  */
bool powerFail = false; 

/**
  * @brief Timer Callback function
  * @details Function triggers motor control loop by setting a Thread Flag
  *          for drive control thread 
  * @param arg : not used
  */
void driveUserTimerCallback(void * arg)
{
    osThreadFlagsSet(driveId,TFLG_DRIVE_START);	
}

void driveThread(void * arg)
{
    driveId = osThreadGetId();
    osThreadSetPriority(driveId, osPriorityAboveNormal3);
    
    leftMotorDescriptor.motSem = osSemaphoreNew(1U,1U,NULL);
    rightMotorDescriptor.motSem = osSemaphoreNew(1U,1U,NULL);
    
    timerId = osTimerNew(driveUserTimerCallback, osTimerPeriodic, NULL, NULL);
    
    uint32_t error;
    
    motorInit();
    
    motPing(&leftMotorDescriptor, &error);
		motPing(&rightMotorDescriptor, &error);
    
    motSetTorque(&leftMotorDescriptor,true,&error);
    motSetTorque(&rightMotorDescriptor,true,&error);
    
    motGetVelocityPosition(&leftMotorDescriptor, &error);
    motGetVelocityPosition(&rightMotorDescriptor, &error);
    
    motClearDistance(leftMotSel);
    motClearDistance(rightMotSel);
    
    osTimerStart(timerId,100);
    
  for(;;)
  {
    osThreadFlagsWait(TFLG_DRIVE_START, osFlagsWaitAny, osWaitForever);
    motSetVelocity(&leftMotorDescriptor, &error);
    motSetVelocity(&rightMotorDescriptor, &error);
    motGetVelocityPosition(&leftMotorDescriptor, &error);
    motGetVelocityPosition(&rightMotorDescriptor, &error);
  }
}
