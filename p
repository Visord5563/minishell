# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/07/20 15:55:57 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror 
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

re: fclean allbultins
execution.c
libft
main.c
makefile
minishell
minishell.h
obj
p
parse_list.c
path_test.c
redirection.c
bultins
execution.c
libft
main.c
makefile
minishell
minishell.h
obj
p
parse_list.c
path_test.c
redirection.c
total 208
drwxr-xr-x  17 ehafiane  candidate    578 Jul 20 17:53 .
drwxr-xr-x  13 ehafiane  candidate    442 Jun 10 14:39 ..
-rw-r--r--   1 ehafiane  candidate   8196 Jul 20 17:04 .DS_Store
drwxr-xr-x  15 ehafiane  candidate    510 Jul 20 17:16 .git
drwxr-xr-x   3 ehafiane  candidate    102 Jul 20 17:05 .vscode
drwxr-xr-x   7 ehafiane  candidate    238 Jul 15 09:13 bultins
-rw-r--r--   1 ehafiane  candidate   3322 Jul 20 17:48 execution.c
drwxr-xr-x  41 ehafiane  candidate   1394 Jul 20 17:05 libft
-rw-r--r--   1 ehafiane  candidate  12199 Jul 20 17:13 main.c
-rw-r--r--   1 ehafiane  candidate   1462 Jul 20 15:55 makefile
-rwxr-xr-x   1 ehafiane  candidate  52648 Jul 20 17:48 minishell
-rw-r--r--   1 ehafiane  candidate   2086 Jul 20 15:55 minishell.h
drwxr-xr-x   6 ehafiane  candidate    204 Jul 20 17:48 obj
-rwxr--r--   1 ehafiane  candidate   1680 Jul 20 17:54 p
-rw-r--r--   1 ehafiane  candidate   1752 Jul 20 15:54 parse_list.c
-rw-r--r--   1 ehafiane  candidate   1143 Jul 13 16:17 path_test.c
-rw-r--r--   1 ehafiane  candidate   1649 Jul 20 15:58 redirection.c
