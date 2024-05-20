
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

/**
  * @addtogroup DRIVEMSGFUNC 
  * @{
  */

/**
  * @brief Function transmit ping to motor
  * @image html ftserDrv-ping-msg-complete.png "Structure of the Ping Message"
  * @details Function sends the ping command to the motor and receives the 
  *          response.\n
  *          Two fields are to be created in the function. 
  *          One field contains the send data. The second field is used to 
  *          store the response. In addition to the basic structure, the 
  *          correct ID of the motor must be entered in the send data. 
  *          Then the data is transmitted and the response is received using 
  *          the @b driveTxRx() function.  Then it is checked whether the 
  *          transmission was error-free. If this is the case, the function 
  *          returns @b true otherwise @b false. If the transmission was error-free, 
  *          the received error code @b ERR is stored in the variable pointed
  *          to by the pointer @b pError, provided that @b pError is not NULL.
  *
  *          @note The buffers must have a size so that the CRC code can be stored 
  *                in them. However, the calculation of the CRC code for the send 
  *                operation is done in the function driveTxRx().
  *
  *          @note When calling the function driveTxRx() the number of bytes 
  *                including the CRC bytes must be specified for the length 
  *                of the send or the receive message.  
  * @param [in]  pmotor : pointer to motor descriptor
  * @param [out] pError : Pointer to variable to store error code from 
  *                       response message.
  *                       Store only, if pError not NULL.
  * @retval State : can be
  *                 @arg true  : no error
  *                 @arg false : error
  */
bool motPing(ftbotMotor_t * pmotor, uint32_t * pError)
{
  uint8_t send[10] = {0xFF, 0xFF, 0xFD, 0x00, pmotor->ID, 0x03, 0x00, 0x01, 0x00, 0x00};
  uint8_t resp[14];
  if (driveTxRx(send, sizeof(send), resp, sizeof(resp), 100) == motCmdOk){
    if (pError != NULL) {
      *pError = resp[8];
    }
    return true;
  }
  return false;  
}

/**
  * @brief Function transmit torque command to motor
  * @image html ftserDrv-write-msg-complete.png "Structure of the Write Message"
  * @image html ftserDrv-Torque-msg-send.png "Structure of the Torque Message"
  * @details Function sends the torque command to the motor and  
  *          receives the response.\n
  *          Two fields are to be created in the function.
  *          One field contains the send data. The second field is used 
  *          to store the response. In addition to the basic structure, 
  *          the correct ID of the motor and the status of the torque 
  *          must be filled in the send data. Then the data is transmitted 
  *          and the response is received using the driveTxRx() function.
  *          Then it is checked whether the transmission was error-free.
  *          If this is the case, the function returns @b true otherwise 
  *          @b false. If the transmission was error-free, the received 
  *          error code @b ERR is stored in the variable pointed to by
  *          the pointer @b pError, provided that @b pError is not @b NULL.
  *
  *          @note The buffers must have a size so that the CRC code can be stored 
  *                in them. However, the calculation of the CRC code for the send 
  *                operation is done in the function driveTxRx().
  *
  *          @note When calling the function driveTxRx() the number of bytes 
  *                including the CRC bytes must be specified for the length 
  *                of the send or the receive message.
  * @param [in]  pmotor : pointer to motor descriptor
  * @param     torqueOn : can be
  *                       @arg true  : torque on
  *                       @arg false : torque off
  * @param [out] pError : Pointer to variable to store error code.
  *                       Store only, if pError not NULL.
  * @retval State : can be
  *                 @arg true  : no error
  *                 @arg false : error
  */
bool motSetTorque(ftbotMotor_t * pmotor, bool torqueOn, uint32_t * pError)
{
  uint8_t send[13] = {0xFF, 0xFF, 0xFD, 0x00, pmotor->ID, 0x06, 0x00, 0x03, 0x40, 0x00, 0x01, 0x00, 0x00};
  uint8_t resp[11];
  if (driveTxRx(send, sizeof(send), resp, sizeof(resp), 100) == motCmdOk){
    if (pError != NULL) {
      *pError = resp[8];
    }
    return true;
  }
  return false;
}

/**
  * @brief Function transmit goal velocity command to motor
  * @image html ftserDrv-write-msg-complete.png "Structure of the Write Message"
  * @image html ftserDrv-goalVel-msg-send.png "Structure of the Set Goal Velocity Message"
  * @details Function sends the set goal velocity command to the motor and  
  *          receives the response. Function set the nominal speed stored in 
  *          @b pmotor structure.\n
  *          There are two fields to be created in the function. One field contains 
  *          the send data. The second field is used to store the response. In the send 
  *          data, besides the basic structure, the correct ID of the motor and the 
  *          value for the <b>Goal Velocity</b> must be entered. The conversion between 
  *          the nominal velocity and the programming value is done with the function 
  *          @b E4speed2GoalVelocity(). Then the data is transferred and the response 
  *          is received using the function @b driveTxRx(). Then it is checked if the 
  *          transmission was error free. If this is the case, the function returns 
  *          @b true otherwise @b false. If the transfer was error-free, the received 
  *          error code @b ERR is stored in the variable pointed to by the pointer 
  *          @b pError, unless @b pError is @b NULL. 
  *
  *          @note The buffers must have a size so that the CRC code can be stored 
  *                in them. However, the calculation of the CRC code for the send 
  *                operation is done in the function driveTxRx().
  *
  *          @note When calling the function driveTxRx() the number of bytes 
  *                including the CRC bytes must be specified for the length 
  *                of the send or the receive message.
  * @param [in]  pmotor : pointer to motor descriptor
  * @param [out] pError : Pointer to variable to store error code.
  *                       Store only, if pError not NULL.
  * @retval State : can be
  *                 @arg true  : no error
  *                 @arg false : error
  */
bool motSetVelocity(ftbotMotor_t * pmotor, uint32_t * pError)
{
  int32_t tmp = speed2GoalVelocity(pmotor->nominalSpeed);    
  uint8_t send[16] = {0xFF, 0xFF, 0xFD, 0x00, pmotor->ID, 0x09, 0x00, 0x03, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t resp[11];
  send[13] = (tmp >> 24) & 0xFF; //tmp & 0xFF000000;
  send[12] = (tmp >> 16) & 0xFF;
  send[11] = (tmp >> 8) & 0xFF;
  send[10] = tmp & 0xFF;
  if (driveTxRx(send, sizeof(send), resp, sizeof(resp), 100) == motCmdOk){
    if (pError != NULL) {
      *pError = resp[8];
    }
    return true;
  }
  return false;
}

/**
  * @brief Function reads present velocity and present position 
  * @image html ftserDrv-read-msg-send.png "Structure of the Read Message - part send"
  * @image html ftserDrv-read-msg-response.png "Structure of the Read Message - part response"
  * @details Function reads present velocity and present position from drive subsystem. 
  *          The speed information and the updated distance traveled value are stored
  *          in the motor descriptor object.\n
  *          Two fields are to be created in the function. One field contains the send 
  *          data. The second field is used to store the response. In addition to the 
  *          basic structure, the correct ID of the motor must be entered in the send data. 
  *          Since the information for <b>Present Velocity</b> (address 128) and 
  *          <b>Present Position</b> (address 132) are in 
  *          consecutive registers, both values can be read out with one transmission. 
  *          Then the data is transferred and the response is received using the 
  *          driveTxRx() function. Then it is checked if the transmission was error 
  *          free. If this is the case, the function returns true otherwise false. 
  *          If the transmission was error-free, the received error code @b ERR is 
  *          stored in the variable pointed to by the pointer @b pError, provided that 
  *          @b pError is not @b NULL. Additionally, the conversion of the register 
  *          value <b>Present Velocity</B> into a velocity in m/s is done using the 
  *          function E4goalVelocity2Speed(). The measured value is stored into the 
  *          motor descriptor structure. The E4motUpdateDistance() function is 
  *          used to update the distance traveled and store the information in 
  *          the motor descriptor structure.
  *
  *          @note The buffers must have a size so that the CRC code can be stored 
  *                in them. However, the calculation of the CRC code for the send 
  *                operation is done in the function driveTxRx().
  *
  *          @note When calling the function driveTxRx() the number of bytes 
  *                including the CRC bytes must be specified for the length 
  *                of the send or the receive message.  
  * @param [in, out] pmotor : pointer to motor descriptor
  * @param [out] pError     : Pointer to variable to store error code.
  *                           Store only, if pError not NULL.
  * @retval State : can be
  *                 @arg true  : no error
  *                 @arg false : error
  */
bool motGetVelocityPosition(ftbotMotor_t * pmotor, uint32_t * pError)
{
  int32_t tmp_s;
  int32_t tmp_p;
  uint8_t send[14] = {0xFF, 0xFF, 0xFD, 0x00, pmotor->ID, 0x07, 0x00, 0x02, 0x80, 0x00, 0x08, 0x00, 0x00, 0x00};
  uint8_t resp[19];
  motcmdState_t tmp = driveTxRx(send, sizeof(send), resp, sizeof(resp), 100);
  if (tmp == motCmdOk){
    tmp_s = resp[9];
    tmp_s |= ((int32_t)resp[10] << 8);
    tmp_s |= ((int32_t)resp[11] << 16);
    tmp_s |= ((int32_t)resp[12] << 24);
    pmotor->currentSpeed = goalVelocity2Speed(tmp_s);
      
    tmp_p = resp[13];
    tmp_p |= ((int32_t)resp[14] << 8);
    tmp_p |= ((int32_t)resp[15] << 16);
    tmp_p |= ((int32_t)resp[16] << 24);
    motUpdateDistance(pmotor, tmp_p);    
    if (pError != NULL) {
      *pError = resp[8];
    }
    return true;
  }
  return false;
}

/**
  * @}
  */ 