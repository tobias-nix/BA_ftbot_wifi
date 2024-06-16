/**
 *******************************************************************************
 * @file      common.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Common header file for all source files
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */
#include "cmsis_os2.h"     // ::CMSIS:RTOS2
#include "stm32f7xx_hal.h" // Keil::Device:STM32Cube HAL:Common
#include "main.h"
#include "ftbot.pb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "pb_encode.h"
#include "pb_decode.h"
