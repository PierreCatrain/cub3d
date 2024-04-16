# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 16:35:51 by picatrai          #+#    #+#              #
#    Updated: 2024/04/16 21:53:43 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MINIFLAGS = -L minilibx-linux -lmlx -lXext -lX11 -lm
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
INCLUDE = -I minilibx-linux -I include
header = ./include/cub3D.h
dir_in_src = $(notdir $(shell find ./src/* -type d))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(header) | obj_dir_create
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)
	@echo "\033[1;32m COMPILED \033[1;37m->\033[4;32m $< \033[0m"

all: $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MINIFLAGS)
	@echo "\n\033[1;33mAll objects have been created\033[0m"

obj_dir_create:
	@if [ ! -d "./obj" ]; then\
		mkdir -p obj;\
	fi;\
	for d in $(dir_in_src); do\
		if [ ! -d ./obj/$$d ]; then\
			mkdir -p ./obj/$$d/;\
		fi;\
	done;\

clean:
	rm -rf $(OBJ) ./obj
	@echo "\033[1;33mAll objects have been deleted\033[0m\n"

fclean: clean
	rm -f $(NAME)
	@echo "\033[1;33mExecutable have been deleted\033[0m\n"

re: fclean all


.PHONY: all clean obj_dir_create
