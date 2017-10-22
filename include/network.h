/*
** network.h for NETWORK_H_ in /home/janel/Live Coding
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Wed Feb 22 21:02:29 2017 Janel
** Last update Sun Oct 22 23:16:39 2017 
*/

#ifndef NETWORK_H_
# define NETWORK_H_

# include <sys/socket.h>
# include <netpacket/packet.h>
# define HARDWARE_LENGTH	6
# define IP_LENGTH		4
# define BROADCAST_ADDR		(uint8_t[6]){0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

/*
** src/network/interface.c
*/
uint8_t				*get_my_mac_address(const int sd, const char interface[const]);
char				get_index_from_interface(struct sockaddr_ll *device, const char interface[const]);

/*
** src/network/network.c
*/
char				send_packet_to_broadcast(const int sd, struct sockaddr_ll *device,
							 const uint8_t *my_mac_address, const char *spoofed_ip_source, const char *victim_ip);
uint8_t				*get_victim_response(const int sd);
char				send_payload_to_victim(const int sd, struct sockaddr_ll *device,
						       const uint8_t *my_mac_address, const char *spoofed_ip_source,
						       const uint8_t *victim_mac_address, const char *victim_ip);

#endif /* !NETWORK_H_ */
