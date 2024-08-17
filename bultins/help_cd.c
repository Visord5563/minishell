/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:45:56 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/17 18:18:23 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "OLDPWD") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

// char	*help_set_env(t_env **env, char *name, char *value, t_env *prev)
// {
// 	t_env	*new_var;

// 	new_var = NULL;
// 	new_var = malloc(sizeof(t_env));
// 	if (!new_var)
// 		return (NULL);
// 	new_var->key = strdup(name);
// 	if (!new_var->key)
// 	{
// 		free(new_var);
// 		return (NULL);
// 	}
// 	new_var->value = strdup(value);
// 	if (!new_var->value)
// 	{
// 		free(new_var->key);
// 		free(new_var);
// 		return (NULL);
// 	}
// 	new_var->next = NULL;
// 	if (prev)
// 		prev->next = new_var;
// 	else
// 		*env = new_var;
// 	return (NULL);
// }

char *set_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (NULL);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}
