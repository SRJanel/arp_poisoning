/*
** misc.c for misc in /home/janel/Projects/tek3/Secu/arp_poisoning/src
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Mon Jan 23 01:59:50 2017 Janel
** Last update Mon Feb 27 03:14:37 2017 Janel
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "error_messages.h"

void		usage(const char prog_name[const])
{
  fprintf(stderr, ERROR_DISPLAY_USAGE, prog_name);
}

uint8_t         *get_hardware_address(const char * const hardware_addr)
{
  uint8_t       *mac;

  if (!(mac = malloc(sizeof(uint8_t) * HARDWARE_LENGTH)))
    return (NULL);
  memcpy(mac, hardware_addr, sizeof(uint8_t) * HARDWARE_LENGTH);
  return (mac);
}
