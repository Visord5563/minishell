/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:15:41 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/20 18:06:09 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int count_argc(char **argv)
{
	int i = 0;
	while (argv[i] != NULL)
		i++;
	return i;
}
int is_n_flag(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n')
	{
		for (int i = 2; arg[i] != '\0'; i++)
		{
			if (arg[i] != 'n')
				return 0;
		}
		return 1;
	}
	return 0;
}

int echo(char **argv)
{
	int i = 1;
	int flag = 0;

	if (count_argc(argv) > 1)
	{
		while (argv[i] && is_n_flag(argv[i]))
		{
			flag = 1;
			i++;
		}
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			if (argv[i+1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
	return 1;
}

int main(int argc, char **argv)
{
	echo(argv);
	return 0;
}