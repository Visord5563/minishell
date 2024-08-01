/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:52:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/27 20:26:50 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchrp(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_val_key(t_env *tmp_env, char *key)
{
	t_env	*new;

	new = tmp_env;
	while (new)
	{
		if (ft_strncmp(new->key, key, ft_strlen(key)) == 0)
			return (1);
		new = new->next;
	}
	return (0);
}

char	*check_value(char *key, t_env *envs)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (free(key), tmp->value);
		tmp = tmp->next;
	}
	return (free(key), "");
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}
