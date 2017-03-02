/*
** packet.c for packet in /home/janel/arp_poisoning
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Thu Feb 23 15:26:13 2017 Janel
** Last update Tue Feb 28 18:23:33 2017 Janel
*/

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include "packets.h"

t_arp_packet	*create_arp_packet(const uint16_t opcode,
				   const uint8_t *my_mac_address, const char *spoofed_ip_source,
				   const uint8_t *destination_mac_address, const char *destination_ip)
{
  t_arp_packet	*arp_packet;

  if (!(arp_packet = malloc(sizeof(t_arp_packet))))
    return (NULL);
  arp_packet->hardware_type = htons(1);
  arp_packet->protocol_type = htons(ETH_P_IP);
  arp_packet->hardware_len = HARDWARE_LENGTH;
  arp_packet->protocol_len = IP_LENGTH;
  arp_packet->opcode = htons(opcode);
  memcpy(&arp_packet->sender_mac, my_mac_address, sizeof(uint8_t) * HARDWARE_LENGTH);
  memcpy(&arp_packet->target_mac, destination_mac_address, sizeof(uint8_t) * HARDWARE_LENGTH);
  if (inet_pton(AF_INET, spoofed_ip_source, arp_packet->sender_ip) != 1
      || inet_pton(AF_INET, destination_ip, arp_packet->target_ip) != 1)
    return (NULL);
  return (arp_packet);
}

t_ethernet_packet	*create_ethernet_packet(const uint8_t *src_mac,
						const uint8_t *dest_mac,
						const t_arp_packet *arp_packet)
{
  t_ethernet_packet	*ethernet_packet;

  if (!(ethernet_packet = malloc(sizeof(uint8_t) * IP_MAXPACKET)))
    return (NULL);
  memcpy(&ethernet_packet->destination_mac_address, dest_mac, sizeof(uint8_t) * HARDWARE_LENGTH);
  memcpy(&ethernet_packet->source_mac_address, src_mac, sizeof(uint8_t) * HARDWARE_LENGTH);
  memcpy(&ethernet_packet->ether_type, (uint8_t[2]){ETH_P_ARP / 256, ETH_P_ARP % 256}, sizeof(uint8_t) * 2);
  memcpy((uint8_t *)ethernet_packet + ETH_HEADER_LENGTH, arp_packet, sizeof(uint8_t) * ARP_HEADER_LENGTH);
  return (ethernet_packet);
}
