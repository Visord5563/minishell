/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:45:45 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/01 04:36:50 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_parse *parse)
{
	int	count;

	count = 0;
	while (parse && parse->token != PIPE)
	{
		if (parse->token == WORD)
		{
			if (parse->flag == 1)
				count += count_str(parse->text, " \t\n\v\f\r");
			else
				count++;
		}
		else if(parse->token == HDOC || parse->token == ROUT || parse->token == APP || parse->token == RIN)
			parse = parse->next;
		parse = parse->next;
	}
	return (count);
}

t_env	*ft_envnew(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	add_env(t_env **envs, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	new = ft_envnew(key, value);
	if (!new)
		return ;
	if (!*envs)
	{
		*envs = new;
		return ;
	}
	tmp = *envs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_env(t_env **envs, char **env)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		add_env(envs, key, value);
		i++;
	}
	add_env(envs, ft_strdup("?"), ft_strdup("0"));
}
