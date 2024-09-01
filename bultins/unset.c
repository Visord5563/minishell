/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:05:26 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/17 11:06:59 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_syntax(t_env **env, char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		exit_status(env, "1");
		return (1);
	}
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
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

void	help_unset( t_env **env, char **names, int i)
{
	t_env	*temp;
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
			if (previous == NULL)
				*env = current->next;
			else
				previous->next = current->next;
			temp = current;
			current = current->next;
			free(temp->key);
			(free(temp->value), free(temp));
			break ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_env **env, char **names)
{
	int		i;

	i = 0;
	while (names[i] != NULL)
	{
		if (check_syntax(env, names[i]) == 0)
			help_unset(env, names, i);
		i++;
	}
	exit_status(env, "0");
}
