# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/11 11:48:17 by hkaddour          #+#    #+#              #
#    Updated: 2022/09/13 11:53:45 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
HEADER = philo.h
CFLAGS = -Wextra -Wall -Werror -g
SRC = main.c\
			philo_utils.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(HEADER)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -r $(NAME)

re: fclean all

.PHONY: all clean fclean re
