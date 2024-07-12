# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 15:43:56 by saharchi          #+#    #+#              #
#    Updated: 2024/07/10 10:14:40 by ehafiane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
ARC = ar rc
SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c\
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
		ft_putendl_fd.c ft_putnbr_fd.c ft_strtrim.c ft_itoa.c ft_split.c ft_strcmp.c\

SRCB =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\

OBJS = $(SRCS:.c=.o)

OBJB = $(SRCB:.c=.o)

$(NAME) : $(OBJS)
	@$(ARC) $(NAME) $(OBJS)

bonus : $(OBJB)
	@$(ARC) $(NAME) $(OBJB)

%.o : %.c libft.h
		@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME) 

clean :
	@$(RM) $(OBJS) $(OBJB)

fclean : clean 
	@$(RM) $(NAME) 

re : fclean all