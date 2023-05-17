# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 10:11:35 by jrouillo          #+#    #+#              #
#    Updated: 2023/04/04 16:33:15 by jrouillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c \
		ft_printf_char.c \
		ft_printf_int_unsigned.c \
		ft_printf_hexa_ptr.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Werror -Wextra

%.o: %.c ft_printf.h
	gcc ${FLAGS} -I. -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) ft_printf.h
	ar -rsc ${NAME} ${OBJS}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re