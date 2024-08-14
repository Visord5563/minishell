/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:11:28 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/14 23:32:35 by mehdi            ###   ########.fr       */
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

void ft_unset(t_env **env, char **names)
{
    int     i;
    t_env   *current;
    t_env   *previous;
    t_env   *temp;

    i = 0;
    while (names[i] != NULL)
    {
        if (check_syntax(env, names[i]) == 0)
        {
            current = *env;
            previous = NULL;
            while (current != NULL)
            {
                if (ft_strcmp(current->key, names[i]) == 0 && ft_strcmp(current->key, "?") != 0)
                {
                    if (previous == NULL)
                        *env = current->next;
                    else
                        previous->next = current->next;

                    temp = current;
                    current = current->next;

                    free(temp->key);
                    free(temp->value);
                    free(temp);
                    break;
                }
                previous = current;
                current = current->next;
            }
        }
        i++;
    }
}

