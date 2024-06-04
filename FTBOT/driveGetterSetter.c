
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern ftbotMotor_t leftMotorDescriptor;
extern ftbotMotor_t rightMotorDescriptor;
extern bool powerFail;

/**
  * @addtogroup DRIVEGETSET 
  * @{
  */

/**
  * @brief Function set power fail state to true
  * @details Functions set content of variable powerFail to true
  */
void setPowerFail(void)
{
powerFail = true;
}

/**
  * @brief Function returns power fail state
  * @details Function returns content of variable powerFail 
  * @retval "Power fail state" : can be:
  *                              @arg true  : power fail is active, robot stops
  *                              @arg false : robot can drive
  */
bool isPowerFail(void)
{
  return powerFail;
}


/**
  * @brief Function to set nominal speed in descriptor variable
  * @details If the global variable powerFail is set to true, the 
  *          target speeds of both motors are set to 0. This causes 
  *          the robot to stop moving.\n
  *          The function only updates the nominal speed within the motor 
  *          descriptor. The setting of the nominal speed of the real 
  *          motor is set using the Drive Thread.
  *          If the nominal speed value exceeds the permitted speed for 
  *          forward or reverse travel, the speed is limited to the 
  *          permitted maximum value. This value is stored as the 
  *          new nominal speed in the descriptor variable.
  * @note The speed limit is also stored in the motor descriptor variable. 
  * @param motSel : Motor selector can be, @b leftMotSel or @b rightMotSel.
  *                   If the selector is invalid, the right motor 
  *                   is controlled.
  * @param  speed : New nominal speed [m/s]
  *
  */
void motSetNomSpeed(motSel_t motSel, float speed)
{
  if (powerFail) {
    leftMotorDescriptor.nominalSpeed = 0.0f;
    rightMotorDescriptor.nominalSpeed = 0.0f;
    return;      
  }
  if (motSel == leftMotSel) {
    if (speed > leftMotorDescriptor.speedLimit) {
    leftMotorDescriptor.nominalSpeed = leftMotorDescriptor.speedLimit;
    } else if (speed < -leftMotorDescriptor.speedLimit) {
      leftMotorDescriptor.nominalSpeed = -leftMotorDescriptor.speedLimit;
    } else {
      leftMotorDescriptor.nominalSpeed = speed;
    }
  } else {
    if (speed > rightMotorDescriptor.speedLimit) {
    rightMotorDescriptor.nominalSpeed = rightMotorDescriptor.speedLimit;
    } else if (speed < -rightMotorDescriptor.speedLimit) {
      rightMotorDescriptor.nominalSpeed = -rightMotorDescriptor.speedLimit;
    } else {
      rightMotorDescriptor.nominalSpeed = speed;  
    }
  }
}


/**
  * @brief Function to get (read) current speed value from descriptor variable
  * @details The function only reads the current speed stored within the motor 
  *          descriptor. The reading of the current speed of the real 
  *          motor is set using the Drive Thread.
  * @param motSel : Motor selector can be, @b leftMotSel or @b rightMotSel.
  *                   If the selector is invalid, the right motor 
  *                   is controlled.
  * @retval  "current speed": current speed [m/s] store in descriptor variable
  *
  */
float motGetCurrSpeed(motSel_t motSel)
{
  float tmp = 0.0f;
  if (motSel == leftMotSel) {
    tmp = leftMotorDescriptor.currentSpeed;
  } else {
    tmp = rightMotorDescriptor.currentSpeed;
  }
  return tmp;
}

/**
  * @brief Function to get (read) current distance value from descriptor variable
  * @details The function only reads the current distance stored within the motor 
  *          descriptor. The reading of the current distance of the real 
  *          motor is set using the Drive Thread.\n
  *          The access to distance variable is protected by the semaphore
  *          stored in the motor descriptor
  * @param motSel : Motor selector can be, @b leftMotSel or @b rightMotSel.
  *                   If the selector is invalid, the right motor 
  *                   is controlled.
  * @retval  "current speed": current speed [m/s] store in descriptor variable
  *
  */
float motGetCurrDistance(motSel_t motSel)
{
  float tmp = 0.0f;
  if (motSel == leftMotSel) {
    osSemaphoreAcquire(leftMotorDescriptor.motSem, osWaitForever);
    tmp = leftMotorDescriptor.distance;
    osSemaphoreRelease(leftMotorDescriptor.motSem);
  } else {
    osSemaphoreAcquire(rightMotorDescriptor.motSem, osWaitForever);
    tmp = rightMotorDescriptor.distance;
    osSemaphoreRelease(rightMotorDescriptor.motSem);
  }
  return tmp;
}

/**
  * @brief Function sets distance value in motor descriptor to 0
  * @details The access to distance variable is protected by the semaphore
  *          stored in the motor descriptor
  * @param motSel : Motor selector can be, @b leftMotSel or @b rightMotSel.
  *                 If the selector is invalid, the right motor 
  *                 is controlled.
  */
void motClearDistance(motSel_t motSel)
{
  if (motSel == leftMotSel) {
    osSemaphoreAcquire(leftMotorDescriptor.motSem, osWaitForever);
    leftMotorDescriptor.distance = 0.0f;
    osSemaphoreRelease(leftMotorDescriptor.motSem);
  } else {
    osSemaphoreAcquire(rightMotorDescriptor.motSem, osWaitForever);
    rightMotorDescriptor.distance = 0.0f;
    osSemaphoreRelease(rightMotorDescriptor.motSem);
  }
}

void motSetVoltage(uint32_t voltage)
{
	
}
/**
  * @}
  */ 