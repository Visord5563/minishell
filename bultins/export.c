/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:13:33 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/11 13:49:36 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void swap_tmp(t_env *tmp, t_env *tmp2)
{
	char *tmp3;

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

void print_export(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void sort_env(t_env **env, int flag)
{
	t_env *tmp;
	t_env *tmp2;

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
	if (flag)
		print_export(*env);
}

int	is_valid_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int ft_export(char **cmd, t_env **env) 
{
	int i;       

	i = 0;
	if (!cmd[1])
		return (sort_env(env, 1), 0);

	
	while (cmd[1][i] && cmd[1][i] != '=')
	{
		
		i++;
		if (!is_valid_key(cmd[1]))
		{
			env_key_error(cmd, env, "export");
			return 0;
		}
		else if (ft_strchr(cmd[1], '='))
		{
			add_env(env, ft_substr(cmd[1], 0, ft_strchr(cmd[1], '=') - cmd[1]), ft_strdup(ft_strchr(cmd[1], '=') + 1));
			set_env(env, ft_substr(cmd[1], 0, ft_strchr(cmd[1], '=') - cmd[1]), ft_strdup(ft_strchr(cmd[1], '=') + 1));
			sort_env(env, 0);
		}
	}   
	
	return 0;
}
