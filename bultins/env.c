/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:59:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/27 01:28:22 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	real_env(t_env *a, t_data *tmp)
{
	while (a != NULL)
	{
		if (ft_strcmp(a->key, "?"))
		{
			if (a->value)
			{
				if (!ft_strcmp(a->key, "PATH"))
				{
					if (tmp->flag == 0)
						printf("%s=%s\n", a->key, a->value);
				}
				else
					printf("%s=%s\n", a->key, a->value);
			}
		}
		a = a->next;
	}
	exit_status(&a, "0");
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

char	*look_for_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
