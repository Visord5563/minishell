# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/06/10 13:43:39 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRC = main.c parse_list.c

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all : $(NAME)

$(LIBFT) : 
	make -C ./libft/

$(NAME) : $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o : %.c minishell.h
		cc $(CFLAGS) -c $<  -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean :
	$(RM) $(OBJ)
	make -C ./libft/ clean
	-rmdir $(OBJDIR)

fclean : clean 
	$(RM) $(NAME)
	make -C ./libft/ fclean

re : fclean all