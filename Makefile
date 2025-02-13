# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 23:55:47 by tuthayak          #+#    #+#              #
#    Updated: 2025/02/12 23:55:47 by tuthayak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTPRINTF = libftprintf
INCLUDES = -I libftprintf/inc -I inc

SRCS_SERVER = server.c minitalk_utils.c
SRCS_CLIENT = client.c minitalk_utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

NAME_SERVER = server
NAME_CLIENT = client

all: $(LIBFTPRINTF)/libftprintf.a $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFTPRINTF) -lftprintf -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFTPRINTF) -lftprintf -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFTPRINTF)/libftprintf.a:
	make -C $(LIBFTPRINTF)

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	make -C $(LIBFTPRINTF) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	make -C $(LIBFTPRINTF) fclean

re: fclean all
