# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/09/29 09:31:43 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c parsing/parse_list.c execution/help_execute.c execution/help_execute_2.c execution/execution.c \
	execution/redirection.c parsing/split.c parsing/exit_status.c bultins/cd.c\
	bultins/help_cd.c bultins/echo.c parsing/parsing.c execution/help_execute_3.c\
	bultins/env.c bultins/export.c bultins/help_export.c bultins/pwd.c\
	bultins/unset.c parsing/herdoc.c parsing/expand.c parsing/add_env.c parsing/add_env_help.c  \
	parsing/delet_quot.c bultins/exit.c bultins/check_bultins.c \
	execution/handle_errors.c parsing/add_cmd.c parsing/new_list.c\
	parsing/parse.c parsing/utils_func.c parsing/utils.c parsing/utils1.c\

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME)

$(OBJDIR)/%.o: %.c inc/minishell.h | $(OBJDIR)
	cc $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/bultins
	mkdir -p $(OBJDIR)/parsing
	mkdir -p $(OBJDIR)/execution

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean
	-rmdir $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all