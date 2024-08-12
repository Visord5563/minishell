/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:13:33 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/12 18:53:00 by ehafiane         ###   ########.fr       */
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
			printf("declare -x %s\n", env->key);
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

int env_key_exists(t_env *env, char *key) 
{
	t_env *current = env;
	
    while (current) 
	{
        if (ft_strcmp(current->key, key) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}


void update_env(t_env **env, char *key, char *value) 
{
    t_env *current = *env;

    while (current) 
	{
        if (ft_strcmp(current->key, key) == 0) 
		{
            free(current->value);
            current->value = value;
            return;
        }
        current = current->next;
    }
}

void add_or_update_env(t_env **env, char *key, char *value)
{
    if (env_key_exists(*env, key))
        update_env(env, key, value);
    else
        add_env(env, key, value);
}

void join_env(t_env *env, char *key, char *value) 
{
	t_env *current = env;

    while (current) 
	{
        if (ft_strcmp(current->key, key) == 0) 
			current->value = ft_strjoin(current->value, value);
        current = current->next;
    }
}

int ft_export(char **cmd, t_env **env) 
{
    int i;
    int flag;
	char *key;
	char *value;
    
    flag = 0;
    i = 1;
    if (!cmd[i])
        return (sort_env(env, 1), 0);

    while (cmd[i])
	{
        if (!is_valid_key(cmd[i])) 
		{
            env_key_error(cmd, env, i, "export");
            return 0;
        }
		else if (is_valid_key(cmd[i]) == 2)
		{
			key = ft_substr(cmd[i], 0, ft_strchr(cmd[i], '+') - cmd[i]);
			value = ft_strdup(ft_strchr(cmd[i], '+') + 2);
			if (env_key_exists(*env, key))
				join_env(*env,key , value);
			else
				add_or_update_env(env, key, value);
			flag = 1;
			(*env) = (*env)->next;
		}
		else if (ft_strchr(cmd[i], '='))
		{
            key = ft_substr(cmd[i], 0, ft_strchr(cmd[i], '=') - cmd[i]);
            value = ft_strdup(ft_strchr(cmd[i], '=') + 1);
            add_or_update_env(env, key, value);
            flag = 1;
        } 
		else 
		{
            char *key = ft_strdup(cmd[i]);
            add_or_update_env(env, key, NULL);
            flag = 1;
        }
        i++;
    }
    if (!flag)   
        sort_env(env, 1);
    return 0;
}
