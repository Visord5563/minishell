/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:15:41 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/13 12:07:05 by ehafiane         ###   ########.fr       */
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

int echo(char **argv)
{
	int i = 1;
	int flag = 0;
	
	if (count_argc(argv) > 1)
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		while (argv[i] != NULL) 
		{
			printf("%s", argv[i]);
			if (argv[i+1] != NULL && argv[i][0] != '\0') {
				printf(" ");
			}
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