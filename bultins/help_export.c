/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:28:29 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/13 12:34:32 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	swap_tmp(t_env *tmp, t_env *tmp2)
{
	char	*tmp3;

	tmp3 = NULL;
	if (ft_strcmp(tmp->key, tmp2->key) > 0)
	{
		tmp3 = tmp->key;
		tmp->key = tmp2->key;
		tmp2->key = tmp3;
		tmp3 = tmp->value;
		tmp->value = tmp2->value;
		tmp2->value = tmp3;
	}
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

void	sort_env(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			swap_tmp(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	print_export(*env);
}

int	is_valid_key(char *var)
{
	int	i;

	i = 0;
	if ((!ft_isalpha(var[i]) && var[i] != '_'))
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+' && var[i + 1] == '=')
			return (2);
		else if ((!ft_isalnum(var[i]) && var[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int	env_key_exists(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
