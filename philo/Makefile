# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/11 11:48:17 by hkaddour          #+#    #+#              #
#    Updated: 2022/09/22 14:09:52 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
HEADER = philo.h
CFLAGS = -Wextra -Wall -Werror -g
PFLAG = -lpthread
SRC = main.c\
			eat.c\
			parsing.c\
			kill.c\
			philo_utils.c
OBJS = $(SRC:.c=.o)

BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPink=\033[1;38;5;205m
BRed=\033[1;31m
BPurple=\033[1;35m

#add flag of -pthreads
all: $(NAME)

$(NAME): tag $(OBJS)
	@echo "$(BGreen)merge $(BBlue)$(OBJS) $(BGreen)$(PFLAG) $(BYellow)output $(BGreen)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(PFLAG) -o $@

%.o: %.c
	@echo "$(BGreen)compile $(BBlue)$^ $(BYellow)to $(BBlue)$@ $(BYellow)link $(BGreen)$(HEADER)"
	@$(CC) $(CFLAGS) -c $< -I $(HEADER)

tag:
	@echo "$(BGreen)"
	@echo "██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝ By hkaddour."
	@echo ""


clean:
	@echo "$(BRed)Clean"
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(BRed)Fclean"
	@rm -r $(NAME)

re: fclean all

.PHONY: all clean fclean re tag
