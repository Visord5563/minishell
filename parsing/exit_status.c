/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 06:57:44 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/13 10:06:12 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_status(t_env **env, char *status)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(status);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
}

int	handle_expand(t_env *env, char *str, int token)
{
	int		fd;
	char	*tmp;

	fd = 0;
	tmp = expand_str(ft_strdup(str), env, 0);
	if (is_space(tmp) || ft_strcmp(tmp, "") == 0)
	{
		tmp = ft_strtrim(tmp, " \t\n\v\f\r");
		if (is_space(tmp) || ft_strcmp(tmp, "") == 0)
			fd = -2;
	}
	if (fd != -2)
	{
		if (token == ROUT)
			fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0764);
		else if (token == APP)
			fd = open(tmp, O_CREAT | O_RDWR | O_APPEND, 0764);
		else
			fd = open(tmp, O_RDONLY, 0644);
	}
	free(tmp);
	return (fd);
}

int	ha_re_in(char *file, t_env *env, int token)
{
	int	fd;

	if (ft_strchr(file, '$'))
	{
		fd = handle_expand(env, file, token);
		return (fd);
	}
	if (!ft_strcmp(file, ""))
		return (-2);
	fd = open(file, O_RDONLY, 0644);
	return (fd);
}

int	ha_re_ou(char *file, t_env *env, int token)
{
	int	fd;

	if (ft_strchr(file, '$'))
	{
		fd = handle_expand(env, file, token);
		return (fd);
	}
	if (token == ROUT)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0764);
	else
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0764);
	return (fd);
}
