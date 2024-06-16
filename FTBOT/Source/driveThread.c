
#include "common.h"
#include "ftbotDrive.h"

/**
  * @addtogroup DRIVETHREAD 
  * @{
  */

#define TFLG_DRIVE_START 0x00000001 /*!< Drive thread Flag for start loop */

typedef struct
{
	float nomSpeedL;  /*!< new nominal speed left */
	float nomSpeedR;  /*!< new nominal  speed right */
	float currSpeedL; /*!< current speed left */
	float currSpeedR; /*!< current speed right */
	float voltage; /*!< voltage from poti with adc1 */
} driveInfo_t;		  /*!< Data type to store data for drive information  */

extern driveInfo_t driveInfo;
extern osMutexId_t driveControlMutId;

osTimerId_t timerId;
osThreadId_t driveId;


/*! Description variable for left motor */
ftbotMotor_t leftMotorDescriptor = {
   .ID = 2,
   .nominalSpeed = 0.0,
   .currentSpeed = 0.0,
   .speedLimit = 0.2f
};

/*! Description variable for right motor */
ftbotMotor_t rightMotorDescriptor = {
   .ID = 3,
   .nominalSpeed = 0.0,
   .currentSpeed = 0.0,
   .speedLimit = 0.2f
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

__NO_RETURN void driveThread(void * arg)
{
    driveId = osThreadGetId();
    osThreadSetPriority(driveId, osPriorityNormal);
 
  for(;;)
  {
	osMutexAcquire(driveControlMutId, osWaitForever);
	driveInfo.currSpeedL = leftMotorDescriptor.nominalSpeed;
	driveInfo.currSpeedR = rightMotorDescriptor.nominalSpeed;
	driveInfo.nomSpeedL = leftMotorDescriptor.nominalSpeed;
	driveInfo.nomSpeedR = rightMotorDescriptor.nominalSpeed;
	leftMotorDescriptor.currentSpeed = leftMotorDescriptor.nominalSpeed;
	rightMotorDescriptor.currentSpeed = rightMotorDescriptor.nominalSpeed;
	osMutexRelease(driveControlMutId);
  }
}
