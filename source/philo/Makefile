# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yademirk <yademirk@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/01 21:37:32 by yademirk          #+#    #+#              #
#    Updated: 2026/03/11 17:48:44 by yademirk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

W_FLAGS = -Wall -Wextra -Werror -g
LIB_FLAGS = -pthread
INC_FLAGS = -I./include/
FLAGS = $(W_FLAGS) -std=c99 -pedantic -pedantic-errors -g $(INC_FLAGS) $(LIB_FLAGS)

SRC_DIR = ./src/
OBJ_DIR = ./obj/

UTILS_DIR = utils/
UTILS_SRC = $(addprefix $(UTILS_DIR), convert.c get_time.c interval_sleep.c philo_message.c)

PHILOSOPHERS_DIR = philosophers/
PHILOSOPHERS_SRC = $(addprefix $(PHILOSOPHERS_DIR), philosophers.c philosophers_routine.c philosophers_utils.c)

C_FILES = main.c mutex.c simulation.c table.c $(UTILS_SRC) $(PHILOSOPHERS_SRC)
SRCS = $(addprefix $(SRC_DIR), $(C_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo Creating the $@ executable...
	@$(CC) $(FLAGS) $(OBJS) -o $@
	@echo Done.

$(OBJ_DIR)%o: $(SRC_DIR)%c
	@mkdir -p $(dir $@)
	@echo Compiling $^...
	@$(CC) $(FLAGS) -c $^ -o $@

clean:
	@echo Cleaning the $(OBJ_DIR) dir...
	@rm -rf $(OBJ_DIR)
	@echo Done.

fclean: clean
	@echo Cleaning the executable $(NAME)...
	@rm -rf $(NAME)
	@echo Done.

re: fclean all

.PHONY: all clean fclean re
