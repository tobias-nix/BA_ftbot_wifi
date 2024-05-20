#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern UART_HandleTypeDef huart1;
/**
  * @addtogroup DRIVEBASECOMFUNC 
  * @{
  */

#define EVT_MOT_RXRDY  0x00000001 /*!< Event flag motor response received */

osSemaphoreId_t sem_id;
osEventFlagsId_t evt_id;


/** 
  * @brief Pointer to response buffer 
  * @details The function @b driveTxRx() writes the address of the buffer for 
  *          storing the receive data into this variable. This is necessary 
  *          because the receive operation is started from the send callback.
  */
static uint8_t * pResponse; 
/** 
  * @brief Size of response message 
  * @details The function @b driveTxRx() writes the number of characters 
  *          to be received in response to the send operation into this 
  *          variable. This is necessary because the receive operation 
  *          is started from the send callback.  
  */
static uint32_t repSize;   


/**
  * @brief Callback for motor command transmitted
  * @details The callback is invoked at the end of a send operation. 
  *          In the callback function the receiving process (interrupt)  
  *          for the response of the drive motor is started.
  *          To do this, the half-duplex connection must be switched to 
  *          receive before the receive function is called. 
  *          Search for the required function in the HAL help.\n
  *          The address of the receive buffer and the number of bytes 
  *          to be received are stored in the global variables 
  *          @b pResponse and @b repSize, respectively.
  * @note If this were done only in the thread, it would not be 
  *       guaranteed that the changeover to reception would be fast 
  *       enough.
  * @param [in] huart : pointer to used UART (not used)
  */
void motorTxCpltCallback( UART_HandleTypeDef *  huart ) 
{
  HAL_HalfDuplex_EnableReceiver(&huart1);
  HAL_UART_Receive_IT(&huart1, pResponse, repSize);
}

/**
  * @brief Callback for motor command response ready
  * @details The callback is invoked at the end of a receive operation. 
  *          It sets the event flag indicating that the 
  *          receive operation is finished.
  * @param [in] huart : pointer to used UART (not used)
  */
void motorRxCpltCallback( UART_HandleTypeDef *  huart ) 
{
  osEventFlagsSet(evt_id, EVT_MOT_RXRDY);
}


/**
  * @brief Function to initialize connection to servo motors
  * @details A semaphore is to be initialized in the function. 
  *          This semaphore is used to ensure that during the actual 
  *          transfer process (sending and receiving the response) the 
  *          transfer function cannot be called again. For the communication 
  *          between the transfer function and the callback functions an event 
  *          flag variable is initialized.\n 
  *          If the library function is used to calculate the CRC code, the 
  *          CRC unit must be initialized with the E4driveCRCinit() function.\n
  * @note If the own function is used for CRC calculation, the call of the 
  *       function must be removed.
  * @details As a further task, the callback functions for the end of the 
  *          send and receive transaction are registered in the function.
  */
void motorInit(void)
{
  sem_id = osSemaphoreNew(1, 1, NULL);
  evt_id = osEventFlagsNew(NULL);
  HAL_UART_RegisterCallback(&huart1, HAL_UART_RX_COMPLETE_CB_ID, motorRxCpltCallback);
  HAL_UART_RegisterCallback(&huart1, HAL_UART_TX_COMPLETE_CB_ID, motorTxCpltCallback);
  //E4driveCRCinit();
}

/**
  * @brief HW function to communicate with robotics servos
  * @image html ftserDrv-ping-msg-complete.png "Example - structure of the Ping Message"
  * @details The function calculates the CRC code of the send message, 
  *          inserts it into the send buffer and then sends it. Then the 
  *          function waits for the arrival of the response. To ensure that 
  *          the response does not contain a transmission error, the CRC code 
  *          of the response is checked. The figure shows the transmission of 
  *          the Ping message as an example.\n
  *          The following steps are necessary for the sending process:
  *          - Check whether the parameters contain valid values. 
  *            Both the pointers and the length of the fields must have 
  *            values other than 0.\n
  *            If this is not the case, the function is terminated 
  *            with the error @b motCmdErrParam.
  *          - The following program section must be protected 
  *            with the semaphore.\n
  *          - Calculate the 16 bit CRC code with the CRC peripheral
  *          - Saving the CRC code in the last two bytes of the send 
  *            field  - CRC1 is low-part of CRC and CRC2 
  *            is the high part.
  *          - Store the address of the receive buffer in the global 
  *            variable @b pResponse. 
  *          - Store the expected length of the motor's response in the 
  *            global variable @b repSize.
  *          - Set communication direction to transmit. See HAL help.
  *          - Start transmit using interrupt. In the case of an error, 
  *            perform the following steps.
  *            - Release Semaphore on error
  *            - Return with error code @b motCmdErrHAL
  *          .
  *          @note The receive process is started by the transmit callback. 
  *                For this reason it is possible to wait immediately for the 
  *                event flag to be set to signal the end of the receive process.
  *
  *          - Wait for Event Flag @b EVT_MOT_RXRDY (timeout). 
  *            In the case of an error, perform the following steps.  
  *            - Abort Receive Operation
  *            - Set communication direction to transmit. See HAL help.
  *            - Release Semaphore on error  
  *            - Return with error code @b motCmdErrTimeout  
  *          - Set communication direction to transmit. See HAL help.
  *            @note The setting of the transmission direction must 
  *                 always be performed. In normal operation and in the 
  *                 case of a fault.\n
  *  
  *          - Calculate the 16 bit CRC code of the received message.
  *          - Compare calculated CRC-Code with received CRC-Code. 
  *            In the case of an error,
  *            - Abort Receive Operation  
  *              @note In rare cases of error, the serial transmission comes out 
  *                    of synchronization, e.g. when the switchover between transmit 
  *                    and receive is too late. This means that the receive block 
  *                    is misaligned. By aborting the receive process, 
  *                    this problem is solved for future transmissions.
  *            - use return code @b motCmdErrCRC, but no return
  *          - Release Semaphore
  *          - Return errorcode or @b motCmdOk
  * @param [in, out] ptxData : pointer to transmit buffer.
  *                            The buffer is so large that the CRC code 
  *                            can be stored in it. However, the CRC code 
  *                            is inserted within the function.
  * @param            txSize : Nr of bytes to transmit.
  *                            The specified length includes the complete 
  *                            message length including the space for the 
  *                            CRC code.
  * @param [out]     prxData : pointer to store response buffer.
  *                            The buffer is so large that the CRC code 
  *                            can be stored in it.
  * @param           rxSize  : Nr of bytes to receive as response
  *                            The specified length includes the complete 
  *                            message length including the space for the 
  *                            CRC code.  
  * @param           timeout : timeout for response from motor
  * @retval "State of command"
  */

// =====================================
// Uncomment function
// =====================================
motcmdState_t driveTxRx(uint8_t * ptxData, uint32_t txSize, 
                        uint8_t * prxData, uint32_t rxSize,
                        uint32_t timeout)
{
  if(txSize==0 || rxSize==0 || ptxData==NULL || prxData==NULL) {
    return motCmdErrParam;
  }
  uint32_t crc_t;
  uint32_t crc_r;
  uint32_t crc_rc;
  osSemaphoreAcquire(sem_id, osWaitForever);
  crc_t = driveCalcCRC(ptxData, txSize-2); //CRC-Code außer beiden letzten Stellen
  ptxData[txSize-2] = crc_t & 0xFF;
  ptxData[txSize-1] = (crc_t >> 8) & 0xFF;
  pResponse = prxData;
  repSize = rxSize;
  HAL_HalfDuplex_EnableTransmitter(&huart1);
  if (HAL_UART_Transmit_IT(&huart1, ptxData, txSize) != HAL_OK){
    osSemaphoreRelease(sem_id);
    return motCmdErrHAL;
  }
  
  if (osEventFlagsWait(evt_id, EVT_MOT_RXRDY, osFlagsWaitAny, timeout) == osErrorTimeout){
    HAL_UART_AbortReceive_IT(&huart1);
    HAL_HalfDuplex_EnableTransmitter(&huart1);
    osSemaphoreRelease(sem_id);
    return motCmdErrTimeout;
  }
  HAL_HalfDuplex_EnableTransmitter(&huart1); //doppel
  crc_rc = driveCalcCRC(prxData, rxSize-2);
  crc_r = (prxData[rxSize-1] << 8) | prxData[rxSize-2];
  if (crc_rc != crc_r) {
    HAL_UART_AbortReceive_IT(&huart1);
    osSemaphoreRelease(sem_id);
    return motCmdErrCRC;
  }
  osSemaphoreRelease(sem_id);
  return motCmdOk;
}

/**
  * @}
  */ 