/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/17 17:25:08 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_space(char str)
{
	if (str == ' ' || (str >= 9 && str <= 13))
		return (1);
	return (0);
}

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
		if (!ft_isdigit(c[i]))
			return (1);
		i++;
	}
	return (0);
}

void	print_exit(char *str)
{
	printf("exit\nminishell: exit: ");
	printf("%s: numeric argument required\n", str);
}

int ft_isstring(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **str, t_env **env)
{
	str[1] = ft_strtrim(str[1], " ");
	if (str[1])
	{
		if (str[2] && !ft_isstring(str[1]))
		{
			printf("exit\nminishell: exit: too many arguments\n");
			exit_status(env, "1");
			return ;
		}
		else if (not_digit(str[1]) == 0)
		{
			printf("exit\n");
			exit(ft_atoi(str[1]) % 256);
		}
		else
			(print_exit(str[1]), exit(255));
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
	exit_status(env, "0");
}
