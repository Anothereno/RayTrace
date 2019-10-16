# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/09 17:56:15 by hdwarven          #+#    #+#              #
#    Updated: 2019/10/16 19:04:15 by hdwarven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = rtv1
INCLUDES = -I ./libft \
           -I ./includes \
           -I ./SDL/SDL2.framework/Versions/A/Headers \
           -I ./SDL/SDL2_ttf.framework/Versions/A/Headers

SRC_PATH = src
SRC_LIST = camera.c      draw.c        light.c       ray_tracing.c vector1.c \
           color.c       events.c      main.c        read_file.c   vector2.c \
           cone.c        init.c        new_objects.c sphere.c \
           cylinder.c    keyboard.c    plane.c       start.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_LIST))

OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_LIST))

LIBFT_PATH = libft
LIBFT = -L $(LIBFT_PATH) -lft

LIBS = -lm \
       -F ./SDL -framework SDL2 \
       -F ./SDL -framework SDL2_ttf


YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

.PHONY: all

all: make_libft intro make_obj $(NAME)
	@echo "$(PURPLE)MAKE $(NAME) Done!$(NC)"

intro:
	@echo "\n$(PURPLE)MAKE $(NAME) Start!$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "$(YELLOW)$(NAME): $(notdir $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES)  -o $@ -c $<

make_obj :
	@mkdir -p obj

make_libft :
	@make -C ./libft/

clean :
	@echo "$(YELLOW)Objects Deleted.$(NC)"
	@/bin/rm -rf $(OBJ_PATH)

fclean :	clean
	@echo "$(YELLOW)$(NAME) Deleted.$(NC)"
	@/bin/rm -f $(NAME)
	@echo "$(YELLOW)Lib_obj Deleted.$(NC)"
	@make -C $(LIBFT_PATH) fclean

re :	fclean all
