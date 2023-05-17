# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 14:03:14 by jrouillo          #+#    #+#              #
#    Updated: 2023/05/17 12:59:14 by jrouillo         ###   ########.fr        #
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

SRC = pipex.c utils.c path.c free.c
SRC2 = $(addprefix $(SRC_PATH), $(SRC))

SRC_BONUS = open.c main_bonus.c init_bonus.c get_next_line_bonus.c \
				utils_bonus.c path_bonus.c free_bonus.c
SCR2_BONUS =$(addprefix $(SRC_BONUS_PATH), $(SRC_BONUS))

############################## OBJECTS ##############################

OBJ = $(SRC:.c=.o)
OBJ2 = $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ2_BONUS = $(addprefix $(OBJ_BONUS_PATH), $(OBJ_BONUS))


############################### FLAGS ###############################

CCF  = cc $(FLAGS)
FLAGS = -Wall -Werror -Wextra -g
#-fsanitize=address -g2


############################## INCLUDE ##############################

INC = -I ./includes/ \
		-I ./libft/ \
		-I ./ft_printf/ \

HDR = includes/pipex.h
HDR_BONUS = includes/pipex_bonus.h


############################### LIBFT ###############################

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a


############################### PRINTF ###############################

PRINTF_PATH = ft_printf
PRINTF = $(PRINTF_PATH)/libftprintf.a


###################### FONT COLORS AND EFFECTS ######################

_GREY=\033[30m
_RED=\033[31m
_GREEN=\033[32m
_YELLOW=\033[33m
_BLUE=\033[34m
_CYAN=\033[36m
_BOLD=\033[1m'


############################### RULES ###############################

all : $(OBJ_PATH) $(LIBFT) $(PRINTF) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	@echo -n "$(_GREY)-${END}"
	@$(CCF) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIBFT):
	@echo "$(_GREY)Compiling Libft...${_END}"
	@make -sC $(LIBFT_PATH)
	@echo "$(_GREEN)\n\n✅ Libft compiled\n${_END}"

$(PRINTF):
	@echo "$(_GREY)Compiling Ft_printf...${_END}"
	@make -sC $(PRINTF_PATH)
	@echo "$(_GREEN)\n\n✅ Ft_printf compiled\n${_END}"

$(NAME): $(OBJ2)
	@echo "$(_GREY)\nCompiling Pipex...${_END}"
	@$(CCF) $(OBJ2) $(LIBFT) $(PRINTF) $(INC) -o $(NAME)
	@echo "$(_GREEN)\n✅ Pipex compiled\n${_END}"
	@echo "$(_GREEN)\n🆗🕺 READY 🕺🆗\n${_END}"

bonus: $(OBJ_BONUS_PATH) $(LIBFT) $(PRINTF) $(OBJ2_BONUS)
	@echo "$(_GREY)\nCompiling Pipex Bonus...${_END}"
	@$(CCF) $(OBJ2_BONUS) $(LIBFT) $(PRINTF) $(INC) -o $(NAME)
	@echo "$(_GREEN)\n✅ Pipex Bonus compiled\n${_END}"
	@echo "$(_GREEN)\n🆗🕺 READY 🕺🆗\n${_END}"

$(OBJ_BONUS_PATH)%.o: $(SRC_BONUS_PATH)%.c $(HDR_BONUS)
	@echo -n "$(_GREY)-${END}"
	@$(CCF) -c $< -o $@ $(INC)

$(OBJ_BONUS_PATH):
	@mkdir $(OBJ_BONUS_PATH)

clean:
	@make clean -sC $(LIBFT_PATH)
	@echo "$(_CYAN)\n🌀 Libft cleaned\n${_END}"
	@make clean -sC $(PRINTF_PATH)
	@echo "$(_CYAN)\n🌀 Ft_printf cleaned\n${_END}"
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ_BONUS_PATH)
	@echo "$(_CYAN)\n🌀 Pipex cleaned\n${_END}"
	@echo "$(_CYAN)🚿🛁 ✧ ALL CLEANED ✧ 🛁🚿\n${_END}"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@make fclean -sC $(PRINTF_PATH)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus