/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:59:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/11 23:48:26 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	real_env(t_env *a, int i, char **cmd)
{
	(void)cmd;
	while (a != NULL)
	{
		if (i == 1)
		{
			if (ft_strcmp(a->key, "?"))
				printf("%s=%s\n", a->key, a->value);
		}
		else
		{
			printf("%s=%s", a->key, a->value);
			if (a->next != NULL)
				printf("\n");
		}
		a = a->next;
	}
}


