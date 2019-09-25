# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/09 17:56:15 by hdwarven          #+#    #+#              #
#    Updated: 2019/09/03 10:27:10 by hdwarven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = wolf3d
INCLUDES = -I ./libft \
           -I ./includes \
           -I ./SDL/SDL2.framework/Versions/A/Headers \
           -I ./SDL/SDL2_ttf.framework/Versions/A/Headers

SRC_PATH = src
SRC_LIST = calculate_distance.c init_hud_and_player.c parse_map.c \
           changing_fullscreen.c init_sdl_ttf.c raycasting.c \
           check_events.c init_weapons.c stats_showing.c colorize.c \
           keys.c stats_weapon.c doors.c load_hud_menu_walls.c \
           timers_game_loop.c draw.c load_weapon.c validation.c \
           errors.c  map_processing.c vert_hor_calc.c exit.c menu.c \
           weapons.c free.c move.c wolf3d.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_LIST))

OBJ_LIST = $(SRC_LIST:.c=.camera)
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
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -camera $(NAME) $(LIBFT)

$(OBJ_PATH)/%.camera: $(SRC_PATH)/%.c
	@echo "$(YELLOW)$(NAME): $(notdir $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES)  -camera $@ -c $<

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
