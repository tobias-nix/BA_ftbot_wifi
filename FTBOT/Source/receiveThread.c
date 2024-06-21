/**
 *******************************************************************************
 * @file      receiveThread.c
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Thread to receive data from the WiFi module
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "receive.h"

#define BUFFER_SIZE 128

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;
extern osEventFlagsId_t EFlagId_ObjInMsgQ;

osThreadId_t receiveId;

/**
 *  @brief Thread to receive data from the WiFi module
 *  @details Receives data from the WiFi module and processes it
 *           The data is expected to be in the format "+IPD,<length>:<data>"
 *           In the <b>super loop</b> the following steps are executed:
 *           1. Wait for the flag to signal that there is an object in the message queue
 *           2. Receive first object from the message queue and check if it is a '+'
 *           3. If it is a '+', receive the next 4 characters and check if it is "+IPD,"
 *           4. If it is "+IPD,", receive the next characters until ':' and extract the length
 *           5. Receive the data until the length is reached
 *           6. Process the received data with the function processReceivedData
 *  @param  [in] arg : Pointer to argument (not used)
 */
__NO_RETURN void receiveThread(void *arg)
{
    receiveId = osThreadGetId();
    osThreadSetPriority(receiveId, osPriorityAboveNormal1);

    static uint8_t buffer_rx[BUFFER_SIZE];
    int buffer_index = 0;

    while (1)
    {
      
        uint8_t msg;
        if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
        {
            if (msg == '+')
            {
                buffer_rx[buffer_index++] = msg;
                for (int i = 1; i <= 4; i++)
                {
                    if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
                    {
                        buffer_rx[buffer_index++] = msg;
                    }
                }

                if (strncmp((char *)buffer_rx, "+IPD,", 5) == 0)
                {
                    do
                    {
                        if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
                        {
                            buffer_rx[buffer_index++] = msg;
                        }
                    } while (msg != ':');

                    char *lengthStart = (char *)buffer_rx + 5; // Message length extraction
                    char *colonPos = strchr(lengthStart, ':');
                    char *dataStart = (char *)buffer_rx;
                    if (colonPos != NULL)
                    {
                        int8_t length = atoi(lengthStart); // Convert the length to an integer
                        buffer_index = 0;

                        // Message extraction
                        for (int i = 0; i < length; i++)
                        {
                            if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
                            {
                                buffer_rx[buffer_index++] = msg;
                            }
                        }
                        //buffer_rx[buffer_index] = '\0';
                        processReceivedData((uint8_t *)dataStart, length); // Message processing (e.g. decoding)
                        buffer_index = 0;                                  // Reset buffer index
                    }
                }
                else
                {
                    buffer_index = 0; // Wrong message format, reset buffer index
                }
            }

            // Reset buffer index if it exceeds the buffer size
            if (buffer_index >= BUFFER_SIZE)
            {
                buffer_index = 0;
                memset(buffer_rx, 0, BUFFER_SIZE);
            }
        }
    }
}

/**
 *  @brief Convert the speed and steering values to wheel speeds
 *  @details Converts the speed and steering values to wheel speeds
 *           The speed and steering values are expected to be in the range [-100, 100]
 *           The wheel speeds are calculated with the following formulas:
 *           leftSpeed = speed * maxWheelSpeed - steering * maxWheelSpeed
 *           rightSpeed = speed * maxWheelSpeed + steering * maxWheelSpeed
 *           The wheel speeds are limited to the maximum range of [-maxWheelSpeed, maxWheelSpeed]
 *  @param  [in] speed : Speed value in the range [-100, 100]
 *  @param  [in] steering : Steering value in the range [-100, 100]
 *  @param  [out] leftSpeed : Pointer to the left wheel speed
 *  @param  [out] rightSpeed : Pointer to the right wheel speed
 */
void convertSpeedSteeringToWheelSpeeds(float speed, float steering, float *leftSpeed, float *rightSpeed)
{
    const float maxWheelSpeed = 0.2f; // Maximum speed for the wheels

    // Normalize the input values to the range [-1, 1]
    float normSpeed = fmaxf(fminf(speed / 100.0f, 1.0f), -1.0f);
    float normSteering = fmaxf(fminf(steering / 100.0f, 1.0f), -1.0f);
  
    float steeringWspeed = (normSteering * normSpeed) / maxWheelSpeed * 0.04f;

    // Calculate the wheel speeds
    *leftSpeed = normSpeed * maxWheelSpeed + steeringWspeed;
    *rightSpeed = normSpeed * maxWheelSpeed - steeringWspeed;

    // Limiting the wheel speeds to the maximum range
    *leftSpeed = fmaxf(fminf(*leftSpeed, maxWheelSpeed), -maxWheelSpeed);
    *rightSpeed = fmaxf(fminf(*rightSpeed, maxWheelSpeed), -maxWheelSpeed);
}

/**
 *  @brief Process the received data
 *  @details Decodes the received data and calculates the nominal speeds for the motors
 *           The received data is expected to be in the format of the nanopb proto message SetSpeedSteering
 *           The function decodes the received data and converts the speed and steering values to the real wheel speeds in m/s
 *           The wheel speeds are then set as the nominal speeds for the motors
 *  @param  [in] data : Pointer to the received data
 *  @param  [in] length : Length of the received data
 */
void processReceivedData(uint8_t *data, size_t length)
{
    ftbot_SetSpeedSteering setSpeedSteering = ftbot_SetSpeedSteering_init_zero;

    pb_istream_t stream = pb_istream_from_buffer(data, length);

    if (!pb_decode(&stream, ftbot_SetSpeedSteering_fields, &setSpeedSteering))
    {
        // Error handling
        return;
    }

    // Convert the speed and steering values to wheel speeds
    float leftSpeed, rightSpeed;
    convertSpeedSteeringToWheelSpeeds(setSpeedSteering.speed, setSpeedSteering.steering, &leftSpeed, &rightSpeed);

    // Set the nominal speeds for the motors
    motSetNomSpeed(leftMotSel, leftSpeed);
    motSetNomSpeed(rightMotSel, rightSpeed);
}