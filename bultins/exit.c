/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/11 12:04:15 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_digit(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (1);
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[i])
	{
		if (c[i] < 48 || c[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit_helper(char **str)
{
	if (str[2])
	{	
		printf("exit\nminishell: exit: too many arguments\n");
		exit(1);
	}
	else if (not_digit(str[1]) == 0)
	{
		printf("exit\n");
		exit(ft_atoll(str[1]) % 256);
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			str[1]);
		exit(255);
	}
}

void	ft_exit(char **str)
{
	if (str[1])
		ft_exit_helper(str);
	else
	{
		printf("exit\n");
		exit(0);
	}
}

int main(int argc, char **argv)
{
	(void)argc;
	ft_exit(argv);
	return (0);
}