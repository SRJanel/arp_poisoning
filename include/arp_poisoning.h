/*
** arp_poisoning.h for ARP_POISONING_H_ in /home/janel/Live Coding
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Wed Feb 22 21:03:39 2017 Janel
** Last update Sun Oct 22 23:17:10 2017 
*/

#ifndef ARP_POISONING_H_
# define ARP_POISONING_H_

# define FALSE				0
# define TRUE				!FALSE
# define SPOOFED_PACKET_SEND_DELAY	1

/*
** src/utils/misc.c
*/
void		usage(const char[const]);
uint8_t         *get_hardware_address(const char * const);

#endif /* !ARP_POISONING_H_ */
