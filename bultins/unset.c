/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:05:26 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/29 09:30:29 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	remove_env_var(t_env **env, t_env *current, t_env *previous)
{
	t_env	*temp;

	if (previous == NULL)
		*env = current->next;
	else
		previous->next = current->next;
	temp = current;
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	help_unset(t_env **env, char **names, int i)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, names[i]) == 0
			&& ft_strcmp(current->key, "?") != 0
			&& ft_strcmp(current->key, "_") != 0)
		{
			remove_env_var(env, current, previous);
			break ;
		}
		else if (!ft_strcmp(current->key, "_"))
		{
			current->flag = 505;
			previous = current;
			current = current->next;
			continue ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_env **env, char **names)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	(*env)->flag = 404;
	while (names[i] != NULL)
	{
		if (check_syntax_export(env, names[i], &flag) == 0)
			help_unset(env, names, i);
		i++;
	}
	if (!flag)
		exit_status(env, "0");
}
