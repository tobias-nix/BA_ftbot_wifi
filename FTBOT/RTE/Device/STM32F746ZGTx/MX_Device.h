/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 01/06/2024 12:33:03
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            16000000
#define MX_HSE_VALUE                            8000000
#define MX_EXTERNAL_CLOCK_VALUE                 12288000
#define MX_SYSCLKFreq_VALUE                     216000000
#define MX_HCLKFreq_Value                       216000000
#define MX_FCLKCortexFreq_Value                 216000000
#define MX_CortexFreq_Value                     216000000
#define MX_AHBFreq_Value                        216000000
#define MX_APB1Freq_Value                       54000000
#define MX_APB2Freq_Value                       108000000
#define MX_APB1TimFreq_Value                    108000000
#define MX_APB2TimFreq_Value                    216000000
#define MX_EthernetFreq_Value                   216000000
#define MX_CECFreq_Value                        32786
#define MX_LCDTFToutputFreq_Value               96000000
#define MX_I2C1Freq_Value                       54000000
#define MX_I2C2Freq_Value                       54000000
#define MX_I2C3Freq_Value                       54000000
#define MX_I2C4Freq_Value                       54000000
#define MX_I2SFreq_Value                        192000000
#define MX_SAI1Freq_Value                       192000000
#define MX_SAI2Freq_Value                       192000000
#define MX_SDMMCFreq_Value                      216000000
#define MX_RTCFreq_Value                        32000
#define MX_USART1Freq_Value                     108000000
#define MX_USART2Freq_Value                     54000000
#define MX_USART3Freq_Value                     54000000
#define MX_UART4Freq_Value                      54000000
#define MX_UART5Freq_Value                      54000000
#define MX_UART8Freq_Value                      54000000
#define MX_UART7Freq_Value                      54000000
#define MX_USART6Freq_Value                     108000000
#define MX_USBFreq_Value                        216000000
#define MX_WatchDogFreq_Value                   32000
#define MX_LPTIM1Freq_Value                     54000000
#define MX_SPDIFRXFreq_Value                    192000000
#define MX_MCO1PinFreq_Value                    16000000
#define MX_MCO2PinFreq_Value                    216000000

/*-------------------------------- ADC1       --------------------------------*/

#define MX_ADC1                                 1

/* GPIO Configuration */

/* Pin PA3 */
#define MX_ADCx_IN3_Pin                         PA3
#define MX_ADCx_IN3_GPIOx                       GPIOA
#define MX_ADCx_IN3_GPIO_PuPd                   GPIO_NOPULL
#define MX_ADCx_IN3_GPIO_Pin                    GPIO_PIN_3
#define MX_ADCx_IN3_GPIO_Mode                   GPIO_MODE_ANALOG

/*-------------------------------- CORTEX_M7  --------------------------------*/

#define MX_CORTEX_M7                            1

/* GPIO Configuration */

/*-------------------------------- CRC        --------------------------------*/

#define MX_CRC                                  1

/* GPIO Configuration */

/*-------------------------------- DMA        --------------------------------*/

#define MX_DMA                                  1

/* NVIC Configuration */

/* NVIC DMA1_Stream6_IRQn */
#define MX_DMA1_Stream6_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream6_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream6_IRQn_Subriority         0

/* NVIC DMA1_Stream5_IRQn */
#define MX_DMA1_Stream5_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream5_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream5_IRQn_Subriority         0

/* NVIC DMA2_Stream6_IRQn */
#define MX_DMA2_Stream6_IRQn_interruptPremptionPriority 0
#define MX_DMA2_Stream6_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA2_Stream6_IRQn_Subriority         0

/* NVIC DMA2_Stream1_IRQn */
#define MX_DMA2_Stream1_IRQn_interruptPremptionPriority 0
#define MX_DMA2_Stream1_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA2_Stream1_IRQn_Subriority         0

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- USART2     --------------------------------*/

#define MX_USART2                               1

#define MX_USART2_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PD5 */
#define MX_USART2_TX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART2_TX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART2_TX_Pin                        PD5
#define MX_USART2_TX_GPIOx                      GPIOD
#define MX_USART2_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART2_TX_GPIO_Pin                   GPIO_PIN_5
#define MX_USART2_TX_GPIO_AF                    GPIO_AF7_USART2

/* Pin PD6 */
#define MX_USART2_RX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART2_RX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART2_RX_Pin                        PD6
#define MX_USART2_RX_GPIOx                      GPIOD
#define MX_USART2_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART2_RX_GPIO_Pin                   GPIO_PIN_6
#define MX_USART2_RX_GPIO_AF                    GPIO_AF7_USART2

/* DMA Configuration */

/* DMA USART2_TX */
#define MX_USART2_TX_DMA_DMA_Handle
#define MX_USART2_TX_DMA_Instance               DMA1_Stream6
#define MX_USART2_TX_DMA_FIFOMode               DMA_FIFOMODE_DISABLE
#define MX_USART2_TX_DMA_Priority               DMA_PRIORITY_LOW
#define MX_USART2_TX_DMA_Channel                DMA_CHANNEL_4
#define MX_USART2_TX_DMA_PeriphDataAlignment    DMA_PDATAALIGN_BYTE
#define MX_USART2_TX_DMA_MemDataAlignment       DMA_MDATAALIGN_BYTE
#define MX_USART2_TX_DMA_Mode                   DMA_NORMAL
#define MX_USART2_TX_DMA_Direction              DMA_MEMORY_TO_PERIPH
#define MX_USART2_TX_DMA_PeriphInc              DMA_PINC_DISABLE
#define MX_USART2_TX_DMA_MemInc                 DMA_MINC_ENABLE
#define MX_USART2_TX_DMA_IpInstance

/* DMA USART2_RX */
#define MX_USART2_RX_DMA_DMA_Handle
#define MX_USART2_RX_DMA_Instance               DMA1_Stream5
#define MX_USART2_RX_DMA_FIFOMode               DMA_FIFOMODE_DISABLE
#define MX_USART2_RX_DMA_Priority               DMA_PRIORITY_LOW
#define MX_USART2_RX_DMA_Channel                DMA_CHANNEL_4
#define MX_USART2_RX_DMA_PeriphDataAlignment    DMA_PDATAALIGN_BYTE
#define MX_USART2_RX_DMA_MemDataAlignment       DMA_MDATAALIGN_BYTE
#define MX_USART2_RX_DMA_Mode                   DMA_CIRCULAR
#define MX_USART2_RX_DMA_Direction              DMA_PERIPH_TO_MEMORY
#define MX_USART2_RX_DMA_PeriphInc              DMA_PINC_DISABLE
#define MX_USART2_RX_DMA_MemInc                 DMA_MINC_ENABLE
#define MX_USART2_RX_DMA_IpInstance

/* NVIC Configuration */

/* NVIC USART2_IRQn */
#define MX_USART2_IRQn_interruptPremptionPriority 0
#define MX_USART2_IRQn_PriorityGroup            NVIC_PRIORITYGROUP_4
#define MX_USART2_IRQn_Subriority               0

/*-------------------------------- USART6     --------------------------------*/

#define MX_USART6                               1

#define MX_USART6_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PC7 */
#define MX_USART6_RX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART6_RX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART6_RX_Pin                        PC7
#define MX_USART6_RX_GPIOx                      GPIOC
#define MX_USART6_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART6_RX_GPIO_Pin                   GPIO_PIN_7
#define MX_USART6_RX_GPIO_AF                    GPIO_AF8_USART6

/* Pin PC6 */
#define MX_USART6_TX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART6_TX_GPIO_Speed                 GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USART6_TX_Pin                        PC6
#define MX_USART6_TX_GPIOx                      GPIOC
#define MX_USART6_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART6_TX_GPIO_Pin                   GPIO_PIN_6
#define MX_USART6_TX_GPIO_AF                    GPIO_AF8_USART6

/* DMA Configuration */

/* DMA USART6_RX */
#define MX_USART6_RX_DMA_MemBurst               DMA_MBURST_SINGLE
#define MX_USART6_RX_DMA_Instance               DMA2_Stream1
#define MX_USART6_RX_DMA_FIFOMode               DMA_FIFOMODE_ENABLE
#define MX_USART6_RX_DMA_Priority               DMA_PRIORITY_MEDIUM
#define MX_USART6_RX_DMA_Channel                DMA_CHANNEL_5
#define MX_USART6_RX_DMA_MemDataAlignment       DMA_MDATAALIGN_BYTE
#define MX_USART6_RX_DMA_Mode                   DMA_CIRCULAR
#define MX_USART6_RX_DMA_Direction              DMA_PERIPH_TO_MEMORY
#define MX_USART6_RX_DMA_PeriphBurst            DMA_PBURST_SINGLE
#define MX_USART6_RX_DMA_MemInc                 DMA_MINC_ENABLE
#define MX_USART6_RX_DMA_IpInstance
#define MX_USART6_RX_DMA_DMA_Handle
#define MX_USART6_RX_DMA_PeriphDataAlignment    DMA_PDATAALIGN_BYTE
#define MX_USART6_RX_DMA_PeriphInc              DMA_PINC_DISABLE
#define MX_USART6_RX_DMA_FIFOThreshold          DMA_FIFO_THRESHOLD_FULL

/* DMA USART6_TX */
#define MX_USART6_TX_DMA_MemBurst               DMA_MBURST_SINGLE
#define MX_USART6_TX_DMA_Instance               DMA2_Stream6
#define MX_USART6_TX_DMA_FIFOMode               DMA_FIFOMODE_ENABLE
#define MX_USART6_TX_DMA_Priority               DMA_PRIORITY_MEDIUM
#define MX_USART6_TX_DMA_Channel                DMA_CHANNEL_5
#define MX_USART6_TX_DMA_MemDataAlignment       DMA_MDATAALIGN_BYTE
#define MX_USART6_TX_DMA_Mode                   DMA_NORMAL
#define MX_USART6_TX_DMA_Direction              DMA_MEMORY_TO_PERIPH
#define MX_USART6_TX_DMA_PeriphBurst            DMA_PBURST_SINGLE
#define MX_USART6_TX_DMA_MemInc                 DMA_MINC_ENABLE
#define MX_USART6_TX_DMA_IpInstance
#define MX_USART6_TX_DMA_DMA_Handle
#define MX_USART6_TX_DMA_PeriphDataAlignment    DMA_PDATAALIGN_BYTE
#define MX_USART6_TX_DMA_PeriphInc              DMA_PINC_DISABLE
#define MX_USART6_TX_DMA_FIFOThreshold          DMA_FIFO_THRESHOLD_FULL

/* NVIC Configuration */

/* NVIC USART6_IRQn */
#define MX_USART6_IRQn_interruptPremptionPriority 0
#define MX_USART6_IRQn_PriorityGroup            NVIC_PRIORITYGROUP_4
#define MX_USART6_IRQn_Subriority               0

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

/* Pin PB14 */
#define MX_PB14_GPIO_Speed                      GPIO_SPEED_FREQ_LOW
#define MX_PB14_Pin                             PB14
#define MX_PB14_GPIOx                           GPIOB
#define MX_PB14_PinState                        GPIO_PIN_RESET
#define MX_PB14_GPIO_PuPd                       GPIO_NOPULL
#define MX_redLed                               PB14
#define MX_PB14_GPIO_Pin                        GPIO_PIN_14
#define MX_PB14_GPIO_ModeDefaultOutputPP        GPIO_MODE_OUTPUT_PP

/* Pin PB7 */
#define MX_PB7_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PB7_Pin                              PB7
#define MX_PB7_GPIOx                            GPIOB
#define MX_PB7_PinState                         GPIO_PIN_RESET
#define MX_PB7_GPIO_PuPd                        GPIO_NOPULL
#define MX_blueLed                              PB7
#define MX_PB7_GPIO_Pin                         GPIO_PIN_7
#define MX_PB7_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

#endif  /* __MX_DEVICE_H */

