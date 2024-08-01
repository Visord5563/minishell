/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:48:40 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/02 00:08:10 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_del(char *del)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	quote = '\0';
	i = 0;
	j = 0;
	if (ft_strchr(del, '$') || ft_strchr(del, '"') || ft_strchr(del, '\''))
	{
		while (del[i])
		{
			j++;
			if (del[i] != '$')
				j = 0;
			if (quote == '\0' && (del[i] == '\'' || del[i] == '"'))
				quote = del[i];
			else if (quote == del[i] && (del[i] == '\'' || del[i] == '"'))
				quote = '\0';
			if (del[i] == '$' && quote == '\0' && (j % 2 != 0) && (del[i + 1] == '\'' || del[i + 1] == '"'))
			{
				new = ft_substr(del, i + 1, ft_strlen(del) - i + 1);
				del = ft_strjoin(ft_substr(del, 0, i), new);
				free(new);
				i--;
			}
			i++;
		}
		del = delete_quotes(ft_strdup(del));
	}
	else
		del = ft_strdup(del);
	return (del);
}

int get_name(char *delimiter)
{
	int fd;
	char	*s;
	char	*runm;
	int i;

	i = 0;
	while (1)
	{
		runm = ft_itoa((int)delimiter + i);
		s = ft_strjoin(ft_strdup("/tmp/."), runm);
		if (open(s, O_RDONLY) == -1)
		{
			fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0744);
			free(runm);
			unlink(s);
			free(s);
			break ;
		}
		i++;
	}
	return (fd);
}

int	heredoc(char *delimiter, t_env *env)
{
	char	*line;
	int		fd;
	char	*del;

	fd = get_name(delimiter);
	g_sigl.sig_herdoc = 1;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		del = check_del(delimiter);
		if (ft_strcmp(line, del) == 0) 
		{
			free(del);
			free(line);
			break ;
		}
		free(del);
		if (ft_strchr(delimiter, '\'') == 0 && ft_strchr(delimiter, '"') == 0)
			line = expend_str(line, env);
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (fd);
}

void	check_heredoc(t_parse **parse, t_env *env)
{
	t_parse	*tmp;
	int		fd;

	fd = 0;
	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			if (fd != 0)
				close(fd);
			tmp->fd_hdoc = heredoc(tmp->next->text, env);
			if (g_sigl.sig_herdoc == 0 || tmp->fd_hdoc == -1)
			{
				dup2(1, 0);
				ft_lstclear(*parse);
				*parse = NULL;
				return ;
			}
			fd = tmp->fd_hdoc;
			tmp = tmp->next;
		}
		if (tmp->token == PIPE)
			fd = 0;
		tmp = tmp->next;
	}
	g_sigl.sig_herdoc = 0;
}
