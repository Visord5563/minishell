/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:28 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/14 23:05:59 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_syntax(t_env **env, char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[i]))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		exit_status(env, "1");
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(env, "1");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(t_env **env, char *name)
{
	t_env	*current;
	t_env	*previous;

	current = *env;
	previous = NULL;
	if (check_syntax(env, name))
		return ;
	while (current != NULL)
	{
		if ((ft_strcmp(current->key, name) == 0) && ft_strcmp(current->key, "?"))
		{
			if (previous == NULL)
				*env = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
