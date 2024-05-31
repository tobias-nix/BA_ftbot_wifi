#include "common.h"
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

extern UART_HandleTypeDef wifi_uart_nix;
extern osMessageQueueId_t MsgQId_nix;

#define BUFFER_SIZE 128

void processReceivedData(uint8_t *data);

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
        uint8_t msg;
        if (osMessageQueueGet(MsgQId_nix, &msg, NULL, osWaitForever) == osOK)
        {
						printf("%s", &msg);
            buffer_rx[buffer_index++] = msg;

            if (msg == '\n')
            {
                buffer_rx[buffer_index] = '\0';
                buffer_index = 0;

                // Überprüfen, ob es sich um +IPD Nachricht handelt
                if (strncmp((char *)buffer_rx, "+IPD,", 5) == 0)
                {
                    char *dataStart = strchr((char *)buffer_rx, ':');
                    if (dataStart != NULL)
                    {
                        dataStart++; // Übergehen des ':' Zeichens
                        processReceivedData((uint8_t *)dataStart);
                    }
                }
            }
        }
    }
}

void convertSpeedSteeringToWheelSpeeds(float speed, float steering, float *leftSpeed, float *rightSpeed)
{
    // Maximalgeschwindigkeit für die Räder
    const float maxWheelSpeed = 0.2f;

    // Normalisieren der Eingabewerte auf den Bereich [-1, 1]
    float normSpeed = fmaxf(fminf(speed / 100.0f, 1.0f), -1.0f);
    float normSteering = fmaxf(fminf(steering / 100.0f, 1.0f), -1.0f);

    // Berechnen der Radgeschwindigkeiten
    *leftSpeed = normSpeed * maxWheelSpeed - normSteering * maxWheelSpeed;
    *rightSpeed = normSpeed * maxWheelSpeed + normSteering * maxWheelSpeed;

    // Begrenzen der Radgeschwindigkeiten auf den maximalen Bereich
    *leftSpeed = fmaxf(fminf(*leftSpeed, maxWheelSpeed), -maxWheelSpeed);
    *rightSpeed = fmaxf(fminf(*rightSpeed, maxWheelSpeed), -maxWheelSpeed);
}

void processReceivedData(uint8_t *data)
{
    ftbot_SetSpeedSteering setSpeedSteering = ftbot_SetSpeedSteering_init_zero;

    pb_istream_t stream = pb_istream_from_buffer(data, strlen((char *)data));

    if (!pb_decode(&stream, ftbot_SetSpeedSteering_fields, &setSpeedSteering))
    {
        // Error handling
        return;
    }

    float leftSpeed, rightSpeed;
    convertSpeedSteeringToWheelSpeeds(setSpeedSteering.speed, setSpeedSteering.steering, &leftSpeed, &rightSpeed);

    motSetNomSpeed(leftMotSel, leftSpeed);
    motSetNomSpeed(rightMotSel, rightSpeed);
}