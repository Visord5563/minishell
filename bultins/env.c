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

void	real_env(t_env *a, int i, char **cmd)
{
	(void)cmd;
	while (a != NULL)
	{
		if (i == 1)
		{
			if (ft_strcmp(a->key, "?"))
			{
				if (a->value)
					printf("%s=%s\n", a->key, a->value);
			}
		}
		a = a->next;
	}
}
