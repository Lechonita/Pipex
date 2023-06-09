# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 14:03:14 by jrouillo          #+#    #+#              #
#    Updated: 2023/05/29 13:51:35 by jrouillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################ PROGRAM NAME ############################

NAME = pipex

# PATH
SRC_PATH = mandatory/
OBJ_PATH = obj_mandatory/

SRC_BONUS_PATH = bonus/
OBJ_BONUS_PATH = obj_bonus/


############################## SOURCES ##############################

SRC = pipex.c open.c utils.c path.c no_path.c free.c
SRC2 = $(addprefix $(SRC_PATH), $(SRC))

SRC_BONUS = pipex_bonus.c open_bonus.c get_next_line_bonus.c \
				utils_bonus.c path_bonus.c no_path_bonus.c free_bonus.c
SCR2_BONUS =$(addprefix $(SRC_BONUS_PATH), $(SRC_BONUS))

############################## OBJECTS ##############################

OBJ = $(SRC:.c=.o)
OBJ2 = $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ2_BONUS = $(addprefix $(OBJ_BONUS_PATH), $(OBJ_BONUS))


############################### FLAGS ###############################

CCF  = cc $(FLAGS)
FLAGS = -Wall -Werror -Wextra


############################## INCLUDE ##############################

INC = -I ./includes/ \
		-I ./libft/ \

HDR = includes/pipex.h
HDR_BONUS = includes/pipex_bonus.h


############################### LIBFT ###############################

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a


###################### FONT COLORS AND EFFECTS ######################

_GREY=\033[30m
_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_CYAN=\033[36m
_BOLD=\033[1m'


############################### RULES ###############################

all : $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	@echo -n "$(_GREY)-${_END}"
	@$(CCF) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIBFT):
	@echo "$(_GREY)Compiling Libft...${_END}"
	@make -sC $(LIBFT_PATH)
	@echo "$(_GREEN)\n\n✅ Libft compiled\n${_END}"

$(NAME): $(OBJ2)
	@echo "$(_GREY)\nCompiling Pipex...${_END}"
	@$(CCF) $(OBJ2) $(LIBFT) $(INC) -o $(NAME)
	@echo "$(_GREEN)\n✅ Pipex compiled\n${_END}"
	@echo "$(_GREEN)\n🆗🕺 READY 🕺🆗\n${_END}"

bonus: $(OBJ_BONUS_PATH) $(LIBFT) $(OBJ2_BONUS)
	@echo "$(_GREY)\nCompiling Pipex Bonus...${_END}"
	@$(CCF) $(OBJ2_BONUS) $(LIBFT) $(INC) -o $(NAME)
	@echo "$(_GREEN)\n✅ Pipex Bonus compiled\n${_END}"
	@echo "$(_GREEN)\n🆗🕺 READY 🕺🆗\n${_END}"

$(OBJ_BONUS_PATH)%.o: $(SRC_BONUS_PATH)%.c $(HDR_BONUS)
	@echo -n "$(_GREY)-${_END}"
	@$(CCF) -c $< -o $@ $(INC)

$(OBJ_BONUS_PATH):
	@mkdir $(OBJ_BONUS_PATH)

clean:
	@make clean -sC $(LIBFT_PATH)
	@echo "$(_CYAN)\n🌀 Libft cleaned\n${_END}"
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ_BONUS_PATH)
	@echo "$(_CYAN)\n🌀 Pipex cleaned\n${_END}"
	@echo "$(_CYAN)🚿🛁 ✧ ALL CLEANED ✧ 🛁🚿\n${_END}"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
