/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:48:40 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/21 14:10:22 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*delet_dollar(char *del, int i, int j)
{
	char	quote;
	char	*new;

	quote = '\0';
	while (del[i])
	{
		j++;
		if (del[i] != '$')
			j = 0;
		if (quote == '\0' && (del[i] == '\'' || del[i] == '"'))
			quote = del[i];
		else if (quote == del[i] && (del[i] == '\'' || del[i] == '"'))
			quote = '\0';
		if (del[i] == '$' && quote == '\0'
			&& (j % 2 != 0) && (del[i + 1] == '\'' || del[i + 1] == '"'))
		{
			new = ft_substr(del, i + 1, ft_strlen(del) - i + 1);
			del = ft_strjoin(ft_substr(del, 0, i), new);
			free(new);
			i--;
		}
		i++;
	}
	return (del);
}

char	*check_del(char *del)
{
	if (ft_strchr(del, '$') || ft_strchr(del, '"') || ft_strchr(del, '\''))
	{
		del = delet_dollar(del, 0, 0);
		del = delete_quotes(ft_strdup(del));
	}
	else
		del = ft_strdup(del);
	return (del);
}

int	get_fd(char *delimiter, int *fd1)
{
	int		fd;
	char	*s;
	char	*runm;
	int		i;

	i = 0;
	while (1)
	{
		runm = ft_itoa((int)delimiter + i);
		s = ft_strjoin(ft_strdup("/tmp/."), runm);
		if (access(s, F_OK | R_OK | W_OK) == -1)
		{
			fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0744);
			*fd1 = open(s, O_RDONLY);
			unlink(s);
			free(runm);
			free(s);
			break ;
		}
		i++;
	}
	return (fd);
}

char	*expand_str_in_her(char *str, t_env *envs, t_flag *flag)
{
	int		i;
	int		j;
	char	quote;

	(1) && (i = 0, j = 0, quote = '\0');
	while (str[i])
	{
		j++;
		if (str[i] != '$')
			j = 0;
		if (str[i])
		{
			if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
				quote = str[i];
			else if (quote == str[i] && (str[i] == '\'' || str[i] == '"'))
				quote = '\0';
			if (str[i] == '$' && ch_fexp(str[i + 1], 0, 0))
				(1) && (str = return_value(str, i, envs, flag), i--);
			if (ft_strcmp(str, "") == 0)
				return (str);
		}
		i++;
	}
	return (str);
}

void	heredoc(char *delimiter, t_env *env, int *fd1)
{
	char	*line;
	int		fd;
	char	*del;
	t_flag	flag;

	flag.flag1 = 0;
	flag.flag = 0;
	flag.quote = '\0';
	fd = get_fd(delimiter, fd1);
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
			line = expand_str_in_her(line, env, &flag);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	check_heredoc(t_parse **parse, t_env *env)
{
	t_parse	*tmp;

	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			heredoc(tmp->next->text, env, &tmp->fd_hdoc);
			if (g_sigl.sig_herdoc == 0 || tmp->fd_hdoc == -1)
			{
				(1) && (dup2(1, 0), ft_lstclear(*parse), *parse = NULL);
				return ;
			}
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	g_sigl.sig_herdoc = 0;
}
