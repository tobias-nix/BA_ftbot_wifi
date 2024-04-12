/**
  ******************************************************************************
  * @file      InitMain.c
  * @author    Tobias Nix
  * @version   V1.0.0
  * @date      12.04.2024
  * @copyright 
  * @brief  Program to initialise parser and configure UART and wifi and to
            send data to pc
  ******************************************************************************
  * @par Change Log:    
  *  @details V1.0.0 Tobias Nix
  *           - Initial version
  ******************************************************************************
  */

// wifi_config.h

#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#define BOT_NAME "FTBOT10" // Set the default bot name here

#ifdef BOT_NAME
    #define IP_ADDRESS_BASE "192.168." // Base IP address

    // Extracting the digits for the IP address from the bot name
    #define IP_ADDRESS_PART1 BOT_NAME[5]
    #define IP_ADDRESS_PART2 BOT_NAME[6]

    // Define IP address as a string
    static const char IP_ADDRESS[] = IP_ADDRESS_BASE IP_ADDRESS_PART1 IP_ADDRESS_PART2 ".1";
    static const char DHCP_POOL_LOW[] = IP_ADDRESS_BASE IP_ADDRESS_PART1 IP_ADDRESS_PART2 ".2";
    static const char DHCP_POOL_HIGH[] = IP_ADDRESS_BASE IP_ADDRESS_PART1 IP_ADDRESS_PART2 ".254";
#else
    #error "Bot name not specified"
#endif

#endif /* WIFI_CONFIG_H */