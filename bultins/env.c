/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:59:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/13 10:06:12 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	real_env(t_env *a)
{
	t_cmd *tmp;

	tmp = malloc(sizeof(t_cmd));
	while (a != NULL)
	{
		if (ft_strcmp(a->key, "?"))
		{
			if (a->value)
			{
				if (!ft_strcmp(a->key, "PATH"))
				{
					if (!tmp->flag)
						printf("%s=%s\n", a->key, a->value);
				}
				else
					printf("%s=%s\n", a->key, a->value);
			}
		}
		a = a->next;
	}
}