/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 04:35:26 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/14 04:38:06 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ha_re_ou(char *file, t_env *env, int token)
{
	int	fd;
	int	flag;

	flag = 0;
	if (ft_strchr(file, '$'))
	{
		fd = handle_expand(env, file, token);
		free(file);
		return (fd);
	}
	if (ft_strchr(file, '\'') || ft_strchr(file, '"'))
		file = delete_quotes(file);
	if (token == ROUT)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
	free(file);
	return (fd);
}

void	print_error(char *text)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("'\n", 2);
}

int	ch_fexp(char c, int i)
{
	if (i == 0 && ((ft_isdigit(c) || ft_isalpha(c) || c == '_' || c == '?')))
		return (1);
	else if (i == 1 && (ft_isdigit(c) || ft_isalpha(c)
			|| c == '_' || c == '?' || c == '"' || c == '\''))
		return (1);
	return (0);
}

int	count_forexp(char *str, int j)
{
	while (str[j] && ch_fexp(str[j], 0))
	{
		if (str[j] == '?')
		{
			j++;
			break ;
		}
		j++;
	}
	return (j);
}

char	*add_quot(char *value, char quote)
{
	char	*s;

	if (ft_strchr(value, '\'') && quote != '"')
	{
		s = value;
		value = ft_strjoin(ft_strdup("\""), s);
		free(s);
		value = ft_strjoin(value, "\"");
	}
	else if (ft_strchr(value, '"') && quote != '"')
	{
		s = value;
		value = ft_strjoin(ft_strdup("\'"), s);
		free(s);
		value = ft_strjoin(value, "\'");
	}
	else if (ft_strchr(value, '"') && quote == '"')
	{
		s = value;
		value = ft_strjoin(ft_strdup("\"\'"), s);
		free(s);
		value = ft_strjoin(value, "\'\"");
	}
	return (value);
}
