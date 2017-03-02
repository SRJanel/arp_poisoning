/*
** debug.h for DEBUG_H_ in /home/janel/Live Coding
**
** Made by Janel
** Login   <janel@epitech.net>
**
** Started on  Wed Feb 22 21:03:21 2017 Janel
** Last update Wed Feb 22 21:03:23 2017 Janel
*/

#ifndef DEBUG_H_
# define DEBUG_H_

# define color_red "\033[1;31m"
# define color_none "\033[0;m"
# define PRINT_MAC_ADDRESS(X)   fprintf(stdout, "|MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", \
					X[0],				\
					X[1],				\
					X[2],				\
					X[3],				\
					X[4],				\
					X[5]);
# define PRINT_IP_ADDRESS(X)    fprintf(stdout, "|IP address: %02d.%02d.%02d.%02d\n", \
					X[0],				\
					X[1],				\
					X[2],				\
					X[3]);

#endif /* !DEBUG_H_ */
