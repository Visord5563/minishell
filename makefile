# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/08/01 22:54:57 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror  -g #-fsanitize=address
RM = rm -f

SRC = main.c parse_list.c execution.c redirection.c split.c bultins/cd.c bultins/echo.c \
	 bultins/export.c bultins/pwd.c herdoc.c expend.c add_env.c delet_quot.c bultins/env.c \
	bultins/exit.c bultins/check_bultins.c add_cmd.c new_list.c parse.c utils_func.c \

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)


all: $(NAME)

$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(OBJDIR)/%.o: %.c minishell.h | $(OBJDIR)
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean
	-rmdir $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all
