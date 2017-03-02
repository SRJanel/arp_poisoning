/*
** interface.c for interface in /home/janel/arp_poisoning
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Thu Feb 23 15:00:25 2017 Janel
** Last update Mon Feb 27 03:29:25 2017 Janel
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <linux/if_arp.h>
#include "arp_poisoning.h"
#include "network.h"

uint8_t		*get_my_mac_address(const int sd, const char interface[const])
{
  struct ifreq	ifr;

  memset(&ifr, 0, sizeof ifr);
  snprintf(ifr.ifr_name, IFNAMSIZ, "%s", interface);
  if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0)
    return (NULL);
  return (get_hardware_address(ifr.ifr_hwaddr.sa_data));
}

char		get_index_from_interface(struct sockaddr_ll *device, const char interface[const])
{
  return ((device->sll_ifindex = if_nametoindex(interface))
	  ? (fprintf(stdout, "[+] Got index '%d' from interface '%s'\n", device->sll_ifindex, interface), TRUE)
	  : (fprintf(stderr, "[-] Could not get index from '%s'\n", interface), FALSE));
}
