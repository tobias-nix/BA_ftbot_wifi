
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

/**
  * @addtogroup DRIVECALCCONV 
  * @{
  */

#define WHEEL_DIAMETER  0.066 /*!< Diameter of wheel 66 mm [m] */
#define VEL_FACTOR      0.229 /*!< 0.229 [rev/min] */
#define MOT_PI          3.14159265358979323846 /*!< PI definition */
#define MAX_GOAL_LIMIT  265  /*!< defined limit of goal velocity value */
#define TICKS_PER_REV   4096 /*!< Number of pulses per turn */

/**
  * @brief Function calculates programming value for goal Velocity
  * @details A speed value in m/s is converted to the required
  *           programming value <b>goal velocity</b> for the motor
  *          (0.229 [rev/min]).
  * @details In the function the calculation is made. It is checked 
  *          whether the calculated value for goal limit is within the 
  *          valid range for the parameter goal velocity. If the calculated 
  *          value exceeds or falls below the allowed range, the calculated 
  *          maximum or minimum value is used.
  * @param speed : desired speed [m/s]
  * @retval "Programming value" in [0.229 rev/min]
  */
int32_t speed2GoalVelocity(float speed)
{
  int32_t tmp = (speed * 60.0f) / (WHEEL_DIAMETER * MOT_PI * VEL_FACTOR);
  if (tmp > MAX_GOAL_LIMIT) {
    return 265;
  }
  if (tmp < -MAX_GOAL_LIMIT){
    return -265;
  }
  return tmp;
}

/**
  * @brief Function calculates speed from raw value goal velocity
  * @details Helper function: The speed in [m/s] is calculated from the 
  *          goal velocity in 0.229[rev/min]..
  * @param goalVelocity : current speed in 0.229[rev/min]
  * @retval Speed in [m/s]
  */
float goalVelocity2Speed(int32_t goalVelocity)
{
  return goalVelocity * (VEL_FACTOR * WHEEL_DIAMETER * MOT_PI / 60.0f);
}

/**
  * @brief Function to update distance value in motor descriptor
  * @details Internal function to update distance from new 
  *          position value read from motor.
  *          - Calculate the difference between last position and current
  *            position in ticks. Use integer arithmetic.
  *          - Calculate the driven distance in m using float arithmetic.
  *          - Update stored distance value in descriptor variable. Access
  *            has to be protected by semaphore stored in motor descriptor.
  *          - Store the new position as old value in motor descriptor 
  *            variable.
  * @param [in, out]  pMotor : pointer to motor descriptor
  * @param            newpos : raw position value read from motor
  *                            (TICKS_PER_REV = 4096 pulses per turn)
  */
void motUpdateDistance(ftbotMotor_t * pMotor, int32_t newpos)
{
  int32_t tmp = newpos  - pMotor->posOld;
  osSemaphoreAcquire(pMotor->motSem,osWaitForever);
  pMotor->distance += ((float) tmp * (WHEEL_DIAMETER * MOT_PI / TICKS_PER_REV));
  osSemaphoreRelease(pMotor->motSem);
  pMotor->posOld = newpos;    
}

/**
  * @}
  */ 