
#include "common.h"
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern ftbotMotor_t leftMotorDescriptor;
extern ftbotMotor_t rightMotorDescriptor;
extern bool powerFail;

float motGetNomSpeed(motSel_t motSel);

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
void motSetNomSpeed(motSel_t motSel, float speed) //Needed
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
float motGetCurrSpeed(motSel_t motSel) //Needed
{
  float tmp = 0.0f;
  if (motSel == leftMotSel) {
    tmp = leftMotorDescriptor.currentSpeed;
  } else {
    tmp = rightMotorDescriptor.currentSpeed;
  }
  return tmp;
}
