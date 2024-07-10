/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:38 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/10 16:50:45 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
#include "./libft/libft.h"

typedef enum s_token
{
	WORD, // simple word
	SQ, // single quote ''
	DQ, // "" double quotes
	HDOC, // << heredoc
	RIN, // < rediction in
	APP, // append >> 
	ROUT, // redirection out >
	PIPE, // |
}	t_token;

typedef struct s_parse
{
	char *text; // cat
	t_token token; // WORD
	int		index; //
	struct s_parse *next;//
} t_parse;

typedef struct s_env
{
	char *key;
	char *value;
	t_parse *parse;
	struct s_env *next;
} t_env;


int echo(char **argv);
int	ft_pwd();

t_parse	*ft_lstnew(char *content, t_token token, int index);
void	ft_lstadd_back(t_parse **lst, t_parse *new);
t_parse	*ft_lstlast(t_parse *lst);
int	ft_lstsize(t_parse *lst);
void	ft_lstclear(t_parse *lst);

#endif