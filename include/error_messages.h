/*
** error_messages.h for ERROR_MESSAGES_H_ in /home/janel/Live Coding
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Wed Feb 22 21:03:10 2017 Janel
** Last update Mon Feb 27 03:17:44 2017 Janel
*/

#ifndef ERROR_MESSAGES_H_
# define ERROR_MESSAGES_H_

# define NEWLINE			"\n"
# define ADD_NEWLINE(STRING)		STRING NEWLINE
# define ERROR_SOCKET_CREATION		ADD_NEWLINE("[-] ERROR: Socket creation failed")
# define ERROR_GET_MAC			ADD_NEWLINE("[-] ERROR: Could not get MAC address")
# define ERROR_PACKET_CREATION_ARP	ADD_NEWLINE("[-] ERROR: ARP packet creation failed")
# define ERROR_PACKET_CREATION_ETHER	ADD_NEWLINE("[-] ERROR: Ether frame creation failed")
# define ERROR_COULD_NOT_SEND		ADD_NEWLINE("[-] ERROR: Could not send")
# define ERROR_COULD_NOT_RECEIVE	ADD_NEWLINE("[-] ERROR: Could not receive")
# define ERROR_DISPLAY_USAGE		ADD_NEWLINE("[*] USAGE: %s source_ip target_ip interface")

#endif /* !ERROR_MESSAGES_H_ */
