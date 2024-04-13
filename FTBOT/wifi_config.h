/**
  ******************************************************************************
  * @file      wifi_config.h
  * @author    Tobias Nix
  * @version   V1.0.0
  * @date      13.04.2024
  * @copyright 
  * @brief  Header file to set ip-address and dhcp range
  ******************************************************************************
  * @par Change Log:    
  *  @details V1.0.0 Tobias Nix
  *           - Initial version
  ******************************************************************************
  */
	
#include <stdlib.h>

#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#define BOT_NAME "FTBOT10" // Set the default bot name here

char* concatenate4Strings(const char *str1, const char *str2, const char *str3, const char *str4);

#ifdef BOT_NAME
    #define IP_ADDRESS_BASE "192.168." // Base IP address

    // Extracting the digits for the IP address from the bot name
    #define IP_ADDRESS_PART1 BOT_NAME[5]
    #define IP_ADDRESS_PART2 BOT_NAME[6]

    // Define IP address as a string
    #define IP_ADDRESS concatenate4Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, &IP_ADDRESS_PART2, ".1");
    #define DHCP_POOL_LOW concatenate4Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, &IP_ADDRESS_PART2, ".2");
    #define DHCP_POOL_HIGH concatenate4Strings(IP_ADDRESS_BASE, &IP_ADDRESS_PART1, &IP_ADDRESS_PART2, ".254");
#else
    #error "Bot name not specified"
#endif

#endif /* WIFI_CONFIG_H */

char* concatenate4Strings(const char *str1, const char *str2, const char *str3, const char *str4) {
    int length = 0;
    const char *temp;
    for (temp = str1; *temp != '\0'; temp++) {
        length++;
    }
    for (temp = str2; *temp != '\0'; temp++) {
        length++;
    }
    for (temp = str3; *temp != '\0'; temp++) {
        length++;
    }
    for (temp = str4; *temp != '\0'; temp++) {
        length++;
    }
    
    char *result = (char*)malloc(length + 1);
    if (result == NULL) {
        exit(1);
    }
    
    char *ptr = result;
    for (const char *s = str1; *s != '\0'; s++) {
        *ptr++ = *s;
    }
    for (const char *s = str2; *s != '\0'; s++) {
        *ptr++ = *s;
    }
    for (const char *s = str3; *s != '\0'; s++) {
        *ptr++ = *s;
    }
    for (const char *s = str4; *s != '\0'; s++) {
        *ptr++ = *s;
    }
    *ptr = '\0';
    
    return result;
}