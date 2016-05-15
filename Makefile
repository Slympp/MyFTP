#!/bin/sh
##
## Makefile for  in /home/antoin_l/Epitech/PSU_2015_malloc
##
## Made by Léo Antoine
## Login	 <antoin_l@epitech.net>
##
## Started on	Thu Feb	11 19:17:48 2016 Léo Antoine
## Last update	Thu Feb	11 19:17:48 2016 Léo Antoine
##

BIN_CLI 			=	client
BIN_SERV 			= 	server

COMMON_SRCS_FILES 	= 	commons.c \
						utils.c \
						utils2.c

CLI_SRCS_FILES 		= 	main.c \
						packet.c \

SERV_SRCS_FILES 	=	main.c \
						packet.c \
						cmd1.c \
						cmd2.c \
						cmd3.c

CMN_SRCS_PATH 		= 	$(addprefix srcs/,$(COMMON_SRCS_FILES))
CLI_SRCS_PATH		= 	$(addprefix srcs/client/,$(CLI_SRCS_FILES))
SERV_SRCS_PATH		= 	$(addprefix srcs/server/,$(SERV_SRCS_FILES))

CMN_OBJS			=	$(CMN_SRCS_PATH:.c=.o)
CLI_OBJS			= 	$(CLI_SRCS_PATH:.c=.o)
SERV_OBJS			= 	$(SERV_SRCS_PATH:.c=.o)

HDR_PATH 	= 	./includes/

CFLAGS 		=  -I$(HDR_PATH) -W -Wall -Wextra -Werror
LIBS		= 	

CC 			= gcc
RM 			= rm -rf

all			: $(BIN_CLI) $(BIN_SERV)

$(BIN_CLI)	: $(CLI_OBJS) $(CMN_OBJS)
			$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BIN_SERV) : $(SERV_OBJS) $(CMN_OBJS)
			$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean		:
			$(RM) $(CLI_OBJS)
			$(RM) $(SERV_OBJS)
			$(RM) $(CMN_OBJS)

fclean		: clean
			$(RM) $(BIN_CLI)
			$(RM) $(BIN_SERV)

re 			: fclean all

.PHONY		: all clean fclean re
