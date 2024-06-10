# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/06/03 19:02:28 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRC = main.c parse_list.c

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(LIBFT) : 
	make -C ./libft/

$(NAME) : $(OBJ) $(LIBFT)
		cc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o : %.c minishell.h
		cc $(CFLAGS) -c $<  -o $@


clean :
	$(RM) $(OBJ)
	make -C ./libft/ clean

fclean : clean 
	$(RM) $(NAME)
	make -C ./libft/ fclean

re : fclean all
