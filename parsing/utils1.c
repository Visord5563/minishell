/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 04:38:56 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/14 04:41:45 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	is_quote(char *text)
{
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	while (text[j] && text[j] != '$')
	{
		if (quote == '\0' && text[j] == '"')
			quote = text[j];
		else if (text[j] == quote)
			quote = '\0';
		j++;
	}
	return (quote);
}

int	count_quotes(char *text)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (text[i] && text[i] != '$')
	{
		if (text[i] == '"')
			j++;
		if (j && text[i] != '"')
			break ;
		i++;
	}
	return (j);
}

void	putstr_her(char *line, char *delimiter, t_env *env, int fd)
{
	t_flag	flag;

	flag.flag = 0;
	flag.quote = '\0';
	if (ft_strchr(delimiter, '\'') == 0 && ft_strchr(delimiter, '"') == 0)
		line = expand_str_in_her(line, env, &flag);
	ft_putendl_fd(line, fd);
	free(line);
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

int	ft_strlen1(char *str, char *set)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && !is_space2(str[i], set))
		i++;
	return (i);
}
