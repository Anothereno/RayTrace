# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/09 17:56:15 by hdwarven          #+#    #+#              #
#    Updated: 2019/10/17 16:05:47 by hdwarven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = rtv1
INCLUDE_FILE = -I ./libft -I ./includes

SRC_PATH = src
SRC_LIST = camera.c      draw.c        light.c       ray_tracing.c vector1.c \
           color.c       events.c      main.c        read_file.c   vector2.c \
           cone.c        init.c        new_objects.c sphere.c \
           cylinder.c    keyboard.c    plane.c       start.c

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH) -lft
ID_UN := $(shell id -un)

SDL_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/include/SDL2
SDL_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2/2.0.10/lib

SDL_TTF_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2
SDL_TTF_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/2.0.15/lib

SDL_MIXER_FOLDER = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/include/SDL2
SDL_MIXER_LIB = /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/2.0.4/lib

LIBS = -L $(LIBFT) -L $(SDL_TTF_LIB) -L $(SDL_MIXER_LIB) -L $(SDL_LIB)  -l SDL2 -l SDL2_ttf -l SDL2_mixer
INCLUDES = $(INCLUDE_FILE) -I $(SDL_TTF_FOLDER) -I $(SDL_MIXER_FOLDER) -I $(SDL_FOLDER)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_LIST))

OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_LIST))


#
# LIBS = -lm \
#        -F ./SDL -framework SDL2 \
#        -F ./SDL -framework SDL2_ttf

YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m


.PHONY: all

all: install_sdl make_libft intro make_obj $(NAME)
	@echo "$(PURPLE)MAKE $(NAME) Done!$(NC)"

install_sdl:
	@brew install sdl2
	@brew switch sdl2 2.0.10
	@brew install sdl2_ttf
	@brew switch sdl2_ttf 2.0.15
	@brew install sdl2_mixer
	@brew switch sdl2_mixer 2.0.4

intro:
	@echo "\n$(PURPLE)MAKE $(NAME) Start!$(NC)"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME)

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
