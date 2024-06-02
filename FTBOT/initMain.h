/**
 *******************************************************************************
 * @file      initMain.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Header file for the main thread
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */
#include "common.h"
#include "initCom.h"
#include "transmitThread.h"
#include "receive.h"
#include "msgQFlagThread.h"
#include "driveThread.h"				// ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotTerminal.h"              // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotLedSWBumper.h"           // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib
#include "ftbotDrive.h"                 // ETTI4::ETTI4 FTbot:EmbSysLab:FTbotLib

char *concatenate3Strings(const char *str1, const char *str2, const char *str3);