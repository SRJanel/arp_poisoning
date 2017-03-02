##
## Makefile for Makefile in /home/janel/arp_poisoning
##
## Made by Janel
## Login   <gianne_n@epitech.net>
##
## Started on  Tue Jul 12 14:07:56 2017 Janel
## Last update Mon Feb 27 03:14:59 2017 Janel
##

SRC	= src/main.c \
	src/utils/misc.c \
	src/network/interface.c \
	src/network/network.c \
	src/network/packet.c \

OBJ	= $(SRC:.c=.o)

NAME	= arp_poisoning

RM	= rm -f

CC	= gcc

CFLAGS	= -std=c99 -Wall -Wextra -Werror
CFLAGS	+= -pedantic-errors
CFLAGS	+= -I./include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
