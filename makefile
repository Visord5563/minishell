# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/07/19 11:14:28 by ehafiane         ###   ########.fr        #
=======
#    Updated: 2024/07/16 23:04:32 by saharchi         ###   ########.fr        #
>>>>>>> salah
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

<<<<<<< HEAD
CFLAGS = #-Wall -Wextra -Werror 
=======
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
>>>>>>> salah
RM = rm -f

SRC = main.c parse_list.c execution.c redirection.c

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

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