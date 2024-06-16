#ifndef DRIVETHREAD_H
#define DRIVETHREAD_H

#include "common.h"
#include "ftbotDrive.h"

/**
  * @addtogroup DRIVETHREAD 
  * @{
  */

#define TFLG_DRIVE_START 0x00000001 /*!< Drive thread Flag for start loop */

extern osTimerId_t timerId;
extern osThreadId_t driveId;

/*! Description variable for left motor */
extern ftbotMotor_t leftMotorDescriptor;

/*! Description variable for right motor */
extern ftbotMotor_t rightMotorDescriptor;

/**
  * @brief Power fail variable
  * @details As soon as the supply voltage falls below a certain level, 
  * the variable is set to true.
  */
extern bool powerFail;

/**
  * @brief Timer Callback function
  * @details Function triggers motor control loop by setting a Thread Flag
  *          for drive control thread 
  * @param arg : not used
  */
void driveUserTimerCallback(void * arg);

/**
  * @brief Drive Thread function
  * @details Main control loop for driving the motors
  * @param arg : not used
  */
void driveThread(void * arg);

#endif // DRIVETHREAD_H
