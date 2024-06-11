
///**
//  ******************************************************************************
//  * @file      InitMain.c
//  * @author    Tobias Nix
//  * @version   V1.0.0
//  * @date      12.04.2024
//  * @copyright 
//  * @brief  Program to initialise parser and configure UART and wifi and to
//            send data to pc
//  ******************************************************************************
//  * @par Change Log:    
//  *  @details V1.0.0 Tobias Nix
//  *           - Initial version
//  ******************************************************************************
//  */

//#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
//#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
//#include "wifi_config.h"
//#include "main.h"
//#include "ftbot.pb.h"
//#include <stdio.h>
//#include <string.h>
//#include <pb_encode.h>

//extern UART_HandleTypeDef wifi_uart_nix;

//osSemaphoreId_t uartTxSemaphore;

//uint16_t buffer_transmit[128] __attribute__((aligned(32)));

///**
//  * @brief Main thread for initialise parser and configure UART and wifi
//  * @details This is the thread which starts after power on
//  *          Init parser
//  *          - checks if all files are there
//  *          Configure serial connection
//  *          - configure UART (baudrate, ...)
//  *          Configure ESP01 "wifi"
//  *          - takes selected name and creates ip
//  *          - creates udp socket
//  *          - generates connection to pc
//  *          - tests connection
//  *          Start next threads
//  *          - reciving thread
//  *          - drive thread
//  *          - at thread
//  * @param  [in] arg : Pointer to argument (not used)
//  */ 

//// Function declarations
//void UART_SendCommand(UART_HandleTypeDef *huart, char* command);
//void UDP_OpenSocket(UART_HandleTypeDef *huart);

//typedef const struct  {
//  const char *str;
//} STRING_LIST_t;

///* Generic responses (see AT_RESP_x definitions) */
//static STRING_LIST_t List_ASCIIResp[] = {
//  { "OK"                },
//  { "ERROR"             },
//  { "FAIL"              },
//  { "SEND OK"           },
//  { "SEND FAIL"         },
//  { "busy p..."         },
//  { "busy s..."         },
//  { "ALREADY CONNECTED" },
//  { "WIFI CONNECTED"    },
//  { "WIFI GOT IP"       },
//  { "WIFI DISCONNECT"   },
//  { "AT"                },
//  { "ready"             },
//  { "ERR CODE"          },
//};

//typedef enum {
//  CMD_IPD         = 0,
//  CMD_CWLAP,
//  CMD_CWJAP_CUR,
//  CMD_CWQAP,
//  CMD_CWSAP_CUR,
//  CMD_CWMODE_CUR,
//  CMD_CWHOSTNAME,
//  CMD_CIPSTAMAC_CUR,
//  CMD_CIPAPMAC_CUR,
//  CMD_RFPOWER,
//  CMD_CIPSTA_CUR,
//  CMD_CIPAP_CUR,
//  CMD_CIPDNS_CUR,
//  CMD_CWDHCP_CUR,
//  CMD_CWDHCPS_CUR,
//  CMD_CWAUTOCONN,
//  CMD_CWLIF,
//  CMD_UART_CUR,
//  CMD_SYSMSG_CUR,
//  CMD_CIPSTATUS,
//  CMD_CIPDOMAIN,
//  CMD_CIPSTART,
//  CMD_CIPCLOSE,
//  CMD_PING,
//  CMD_CIPSEND,
//  CMD_CIPMUX,
//  CMD_CIPSERVER,
//  CMD_CIPSERVERMAXCONN,
//  CMD_RST,
//  CMD_GMR,
//  CMD_LINK_CONN,
//  CMD_STA_CONNECTED,
//  CMD_STA_DISCONNECTED,
//  CMD_SLEEP,
//  CMD_ECHO        = 0xFD, /* Command Echo                 */
//  CMD_TEST        = 0xFE, /* AT startup (empty command)   */
//  CMD_UNKNOWN     = 0xFF  /* Unknown or unhandled command */
//} CommandCode_t;
//  


//typedef struct {
//  uint32_t  baudrate;
//  uint8_t   databits;
//  uint8_t   stopbits;
//  uint8_t   parity;
//  uint8_t   flow_control;
//} COM_UART_INTERFACE;

//  // Initialize Protobuf parser
//void protobuf_init() {
//    // Your initialization code here
//}

//// Initialize UART communication with ESP-01
//void uart_init() {
//  char txData[] = "AT\r\n";
//  char rxData[18];
//  
//  while(1) {
//  HAL_UART_Transmit_IT(&wifi_uart_nix, (uint8_t *)txData, strlen(txData));
//  }
//  while (HAL_UART_GetState(&wifi_uart_nix) != HAL_UART_STATE_READY);
//  HAL_UART_Receive_DMA(&wifi_uart_nix, (uint8_t *)rxData, sizeof(rxData));

//  while (HAL_UART_GetState(&wifi_uart_nix) != HAL_UART_STATE_READY);
//  
//  //if (rxData == )
//    
//  
//}

//// Initialize ESP-01 WiFi module
//void wifi_init() {
//    // Your initialization code here
//}

//// Receiving thread function
//void receivingThread(void *argument) {
//    while (1) {
//        // Receive data and process
//    }
//}

//// Drive thread function
//void driveThread(void *argument) {
//    while (1) {
//        // Control motor or drive
//    }
//}

//// AT command thread function
//void atThread(void *argument) {
//    while (1) {
//        // Send AT commands to ESP-01
//    }
//}

//// Transmit thread function
//void transmitThread(void *argument) {
//    
//    static uint8_t buffer_stream[128];
//  
//   uartTxSemaphore = osSemaphoreNew(2U, 2U, NULL);
//  
//    
//    static const char command[] = "AT\r\n";
//    // Start DMA transfer for transmitting command
//  if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK) {
//    HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t *) command, sizeof(command));
//  }
//    
//    
//    static const char udpCommand[] = "AT+CIPSTART=\"UDP\",\"192.168.10.2\",55719,58361,0\r\n";

//    // Reset the transfer complete flag
//    

//    // Start DMA transfer for transmitting UDP command
//  if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK) {
//    HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t*)udpCommand, sizeof(udpCommand));
//  }
//    // Wait for the DMA transfer to complete
//    
//  
//	ftbot_RobotStatus robotStatus = ftbot_RobotStatus_init_zero;
//  
//  robotStatus.true_left_speed = 3.0;
//  robotStatus.true_right_speed = 5.0;
//  robotStatus.voltage = 12.0;
//  
//  pb_ostream_t stream = pb_ostream_from_buffer(buffer_stream, sizeof(buffer_stream));
//  
//  if (!pb_encode(&stream, ftbot_RobotStatus_fields, &robotStatus)) {
//        // Error Handling
//        return;
//  }
//  
//  while (1) {
//        
//        // static const char atCommand[] = "AT+CIPSEND=10\r\n"; // so funktioniert es
//        SCB_InvalidateDCache_by_Addr(&buffer_transmit[0], 2*sizeof(uint16_t));
//        int commandLength = snprintf((char *) buffer_transmit, sizeof(buffer_transmit), "AT+CIPSEND=%d\r\n", stream.bytes_written);

//        // Sende den AT-Befehl �ber UART an das WiFi-Modul
//    if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK) {
//        HAL_UART_Transmit_DMA(&wifi_uart_nix, (uint8_t *)buffer_transmit, commandLength);
//    }
//        
//    if (osSemaphoreAcquire(uartTxSemaphore, osWaitForever) == osOK) {
//        HAL_UART_Transmit_DMA(&wifi_uart_nix, buffer_stream, stream.bytes_written);
//    }  

//        osDelay(1000); // Zum Beispiel alle 1000 ms senden
//    }
//  
//}

//void UART_SendCommand(UART_HandleTypeDef *huart, char* command)
//{
//    HAL_UART_Transmit(huart, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
//}

//void UDP_OpenSocket(UART_HandleTypeDef *huart)
//{
//    char udpCommand[50];
//    sprintf(udpCommand, "AT+CIPSTART=\"UDP\",\"192.168.10.2\",55719,58361,0\r\n");
//    UART_SendCommand(huart, udpCommand);
//}

//void UART_SendCommand_DMA(UART_HandleTypeDef *huart, char* command)
//{
//    // Start DMA transfer for transmitting command
//    HAL_UART_Transmit_DMA(huart, (uint8_t*)command, sizeof(command));
//}

//void UDP_OpenSocket_DMA(UART_HandleTypeDef *huart)
//{
//    static const char udpCommand[] = "AT+CIPSTART=\"UDP\",\"192.168.10.2\",55719,58361,0\r\n";

//    // Start DMA transfer for transmitting UDP command
//    HAL_UART_Transmit_DMA(huart, (uint8_t*)udpCommand, sizeof(udpCommand));
//}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//    osSemaphoreRelease(uartTxSemaphore);
//}


//__NO_RETURN void mainThread(void * arg)
//{
//  // char *ip = IP_ADDRESS;
//  
//  // UART_SendCommand(wifi_uart_nix, "AT\r\n");
//	// HAL_Delay(1000);
//	// UDP_OpenSocket(wifi_uart_nix);
//	
//  // UART_SendCommand_DMA(&wifi_uart_nix, "AT\r\n");
//	// UDP_OpenSocket_DMA(&wifi_uart_nix);
//  
//  
//  // protobuf_init();
//  // uart_init();
//  // wifi_init();
//  
//  // Start receiving thread
//  // osThreadNew(receivingThread, NULL, NULL);

//  // Start drive thread
//  // osThreadNew(driveThread, NULL, NULL);

//  // Start AT command thread
//  // osThreadNew(atThread, NULL, NULL);

//	osThreadNew(transmitThread, NULL, NULL);

//  // Start scheduler
//  // osKernelStart();
//  
//  for(;;) {
//    
//  }
//}
