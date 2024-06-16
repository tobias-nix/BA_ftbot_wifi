/**
 *******************************************************************************
 * @file      initCom.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Header file for the initialization
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"

bool file_exists(const char *filename);
int8_t protobuf_init();
int8_t uart_init();
int8_t wifi_init();