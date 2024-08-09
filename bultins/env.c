/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:59:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/09 13:44:18 by ehafiane         ###   ########.fr       */
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

void	export_env(t_env *a ,char **cmd)
{
	(void)cmd;
	while (a != NULL)
	{
			if (ft_strcmp(a->key, "?"))
				printf("declare -x %s=\"%s\"\n", a->key, a->value);
			if (ft_strcmp(a->key, "?") && !a->value)
				printf("declare -x %s=%s\n", a->key, a->value);
				
		a = a->next;
	}
}
