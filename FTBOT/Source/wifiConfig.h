/**
 *******************************************************************************
 * @file      wifi_config.h
 * @author    Tobias Nix
 * @version   V0.1.0
 * @date      30.06.2024
 * @copyright 2024 Tobias Nix
 * @brief     Configuration file for the WiFi module
 *******************************************************************************
 * @par Change log:
 *  @details V0.1.0 Tobias Nix
 *           - Initial version
 *******************************************************************************
 */

#include "common.h"

#define BOT_NAME "FTBOT10" // Set the default bot name here

// Restriction: Users should only modify the BOT_NAME, do not change other constants!
//--------------------------------------------------------------------------------

#ifdef BOT_NAME
#define IP_ADDRESS_BASE "192.168." // Base IP address

// Extracting the digits for the IP address from the bot name
#define IP_ADDRESS_PART1 BOT_NAME[5]

// Define IP address as a string
#define IP_ADDRESS_FTBOT concatenate3Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, ".1")
#define IP_ADDRESS_CONTROL concatenate3Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, ".2")
#define DHCP_POOL_LOW concatenate3Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, ".2")
#define DHCP_POOL_HIGH concatenate3Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, ".102")
#else
#error "Bot name not specified"
#endif

/**
 *  @brief Concatenate 3 strings to one
 *  @details Three strings are concatenated to one string
 *           Function determines the length of the concatenated string and allocates memory
 *          for the new string. The strings are copied to the new string.
 *  @param  [in] str1 : pointer to first string
 *  @param  [in] str2 : pointer to second string
 *  @param  [in] str3 : pointer to third string
 *  @retval char* : pointer to the concatenated string
 */
char *concatenate3Strings(const char *str1, const char *str2, const char *str3)
{
    int length = 0;
    const char *temp;
    for (temp = str1; *temp != '\0'; temp++)
    {
        length++;
    }
    for (temp = str2; *temp != '\0'; temp++)
    {
        length++;
    }
    for (temp = str3; *temp != '\0'; temp++)
    {
        length++;
    }

    char *result = (char *)malloc(length + 1);
    if (result == NULL)
    {
        exit(1);
    }

    char *ptr = result;
    for (const char *s = str1; *s != '\0'; s++)
    {
        *ptr++ = *s;
    }
    for (const char *s = str2; *s != '\0'; s++)
    {
        *ptr++ = *s;
    }
    for (const char *s = str3; *s != '\0'; s++)
    {
        *ptr++ = *s;
    }
    *ptr = '\0';

    return result;
}