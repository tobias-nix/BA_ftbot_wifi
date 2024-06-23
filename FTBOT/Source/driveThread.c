/**
 *******************************************************************************
 * @file      driveThread.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      23.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Drive thread for the FTBot
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"

extern osMutexId_t driveControlMutId;

osThreadId_t driveId;

/*! Description variable for left motor */
ftbotMotor_t leftMotorDescriptor = {
    .ID = 2,
    .nominalSpeed = 0.0,
    .currentSpeed = 0.0,
    .speedLimit = 0.2f};

/*! Description variable for right motor */
ftbotMotor_t rightMotorDescriptor = {
    .ID = 3,
    .nominalSpeed = 0.0,
    .currentSpeed = 0.0,
    .speedLimit = 0.2f};

/**
 * @brief Main drive thread function
 * @details This function represents the main execution body of the drive thread. 
 *          It continuously updates the current speed of both motors 
 *          to their nominal speeds within a mutex-protected block, ensuring 
 *          thread-safe access to shared resources. The thread then waits for a 
 *          specified delay before repeating the process. This loop runs indefinitely 
 *          until the thread is terminated externally.
 * @param  [in] arg : Pointer to argument (not used).
 */
__NO_RETURN void driveThread(void *arg)
{
  driveId = osThreadGetId();
  osThreadSetPriority(driveId, osPriorityNormal);

  for (;;)
  {
    osMutexAcquire(driveControlMutId, osWaitForever);
    leftMotorDescriptor.currentSpeed = leftMotorDescriptor.nominalSpeed;
    rightMotorDescriptor.currentSpeed = rightMotorDescriptor.nominalSpeed;
    osMutexRelease(driveControlMutId);
    osDelay(40);
  }
}
