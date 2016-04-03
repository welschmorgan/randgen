#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/03 12:33:39 by mwelsch           #+#    #+#              #
#    Updated: 2016/04/03 14:49:48 by mwelsch          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = randgen

SRCS = $(shell find . -name "*.c" -maxdepth 1 -mindepth 1 -type f)
OBJS = $(patsubst %.c,%.o,$(SRCS))

CFLAGS = -g -Wall -Werror -Wextra
LDFLAGS =

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

all: $(NAME)

.PHONY: clean fclean all re