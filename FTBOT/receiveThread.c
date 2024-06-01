#include "common.h"
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;
extern osEventFlagsId_t EFlagId_ObjInMsgQ;

#define BUFFER_SIZE 128

void processReceivedData(uint8_t *data, size_t length);

/**
 *  @brief Brief description
 *  @details More details
 *  @param [in] argument Description for argument
 *  @return Return description
 */
void receiveThread(void *arg)
{
    static uint8_t buffer_rx[BUFFER_SIZE];
    size_t buffer_index = 0;

    while (1)
    {
        osEventFlagsWait(EFlagId_ObjInMsgQ, 0x00000001U, osFlagsWaitAny, osWaitForever);

        uint8_t msg;
        if (osMessageQueueGet(MsgQId_nix, &msg, NULL, 10) == osOK)
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

                buffer_rx[buffer_index] = '\0';

                if (strncmp((char *)buffer_rx, "+IPD,", 5) == 0)
                {
									do
									{
										if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
										{
											buffer_rx[buffer_index++] = msg;
										}
									}
									while (msg != ':');
										
                    // Länge der Nachricht einlesen
                   char *lengthStart = (char *)buffer_rx + 5;
                   char *colonPos = strchr(lengthStart, ':');
									 char *dataStart = colonPos + 1;
                   if (colonPos != NULL)
                    {
                        int8_t length = atoi(lengthStart); // Konvertiert die Länge
                        buffer_index = 0;

                        // Nachricht nach dem Präfix empfangen
                        for (int i = 0; i < length; i++)
                        {
                            if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
                            {
                                buffer_rx[buffer_index++] = msg;
                            }
                        }
												
                        buffer_rx[buffer_index] = '\0';

                        // Nachricht verarbeiten
                        processReceivedData((uint8_t *)dataStart, length);

                        // Puffer zurücksetzen
                        buffer_index = 0;
                    }
                }
                else
                {
                    buffer_index = 0; // Ungültiges Präfix, zurücksetzen
                }
            }

            // Falls der Puffer überläuft, zurücksetzen
            if (buffer_index >= BUFFER_SIZE)
            {
                buffer_index = 0;
                memset(buffer_rx, 0, BUFFER_SIZE);
            }
        }
    }
}

void convertSpeedSteeringToWheelSpeeds(float speed, float steering, float *leftSpeed, float *rightSpeed)
{
    // Maximum speed for the wheels
    const float maxWheelSpeed = 0.2f;

    // Normalize the input values to the range [-1, 1]
    float normSpeed = fmaxf(fminf(speed / 100.0f, 1.0f), -1.0f);
    float normSteering = fmaxf(fminf(steering / 100.0f, 1.0f), -1.0f);

    // Calculate the wheel speeds
    *leftSpeed = normSpeed * maxWheelSpeed - normSteering * maxWheelSpeed;
    *rightSpeed = normSpeed * maxWheelSpeed + normSteering * maxWheelSpeed;

    // Limiting the wheel speeds to the maximum range
    *leftSpeed = fmaxf(fminf(*leftSpeed, maxWheelSpeed), -maxWheelSpeed);
    *rightSpeed = fmaxf(fminf(*rightSpeed, maxWheelSpeed), -maxWheelSpeed);
}

void processReceivedData(uint8_t *data, size_t length)
{
    ftbot_SetSpeedSteering setSpeedSteering = ftbot_SetSpeedSteering_init_zero;

    pb_istream_t stream = pb_istream_from_buffer(data, length);

    if (!pb_decode(&stream, ftbot_SetSpeedSteering_fields, &setSpeedSteering))
    {
        // Error handling
        return;
    }

    // Konvertieren der empfangenen Daten in Radgeschwindigkeiten
    float leftSpeed, rightSpeed;
    convertSpeedSteeringToWheelSpeeds(setSpeedSteering.speed, setSpeedSteering.steering, &leftSpeed, &rightSpeed);

    // Setzen der nominalen Geschwindigkeiten für die Motoren
    motSetNomSpeed(leftMotSel, leftSpeed);
    motSetNomSpeed(rightMotSel, rightSpeed);
}