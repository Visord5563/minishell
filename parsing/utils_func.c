/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:52:48 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/16 10:16:19 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*check_value(char *key, t_env *envs, int flag)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (flag == 1)
			{
				if (ft_strcmp(tmp->key, "_") == 0)
					return (free(key), "");
				else if (ft_strcmp(tmp->key, "?") == 0)
					return (free(key), ft_strdup("0"));
			}
			if (tmp->value)
				return (free(key), ft_strdup(tmp->value));
		}
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

void	print_error_quote(char quote)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
}
