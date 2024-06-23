/**
 *******************************************************************************
 * @file      driveGetterSetter.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      23.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Getter and Setter functions for the motor descriptor variables
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"
#include "ftbotDrive.h" // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern ftbotMotor_t leftMotorDescriptor;
extern ftbotMotor_t rightMotorDescriptor;

float motGetNomSpeed(motSel_t motSel);

/**
 * @brief Function to set nominal speed in descriptor variable
 * @details The function only updates the nominal speed within the motor
 *          descriptor.
 *          If the nominal speed value exceeds the permitted speed for
 *          forward or reverse travel, the speed is limited to the
 *          permitted maximum value. This value is stored as the
 *          new nominal speed in the descriptor variable.
 * @param motSel : Motor selector can be, @b leftMotSel or @b rightMotSel.
 *                   If the selector is invalid, the right motor
 *                   is controlled.
 * @param  speed : New nominal speed [m/s]
 *
 */
void motSetNomSpeed(motSel_t motSel, float speed) // Needed
{
  if (motSel == leftMotSel)
  {
    if (speed > leftMotorDescriptor.speedLimit)
    {
      leftMotorDescriptor.nominalSpeed = leftMotorDescriptor.speedLimit;
    }
    else if (speed < -leftMotorDescriptor.speedLimit)
    {
      leftMotorDescriptor.nominalSpeed = -leftMotorDescriptor.speedLimit;
    }
    else
    {
      leftMotorDescriptor.nominalSpeed = speed;
    }
  }
  else
  {
    if (speed > rightMotorDescriptor.speedLimit)
    {
      rightMotorDescriptor.nominalSpeed = rightMotorDescriptor.speedLimit;
    }
    else if (speed < -rightMotorDescriptor.speedLimit)
    {
      rightMotorDescriptor.nominalSpeed = -rightMotorDescriptor.speedLimit;
    }
    else
    {
      rightMotorDescriptor.nominalSpeed = speed;
    }
  }
}

/**
 * @brief Function to read current speed value from descriptor variable
 * @details The function only reads the current speed stored within the motor
 *          descriptor.
 * @param motSel : Motor selector can be, @b leftMotSel or @b rightMotSel.
 *                   If the selector is invalid, the right motor
 *                   is controlled.
 * @retval  "current speed": current speed [m/s] store in descriptor variable
 *
 */
float motGetCurrSpeed(motSel_t motSel) // Needed
{
  float tmp = 0.0f;
  if (motSel == leftMotSel)
  {
    tmp = leftMotorDescriptor.currentSpeed;
  }
  else
  {
    tmp = rightMotorDescriptor.currentSpeed;
  }
  return tmp;
}
