/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/31 17:52:07 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int not_digit(char *c)
{
    int i = 0;
    if (!c)
        return 1;
    if (c[0] == '-' || c[0] == '+')
        i++;
    while (c[i])
    {
        if (!ft_isdigit(c[i]))
            return 1;
        i++;
    }
    return 0;
}

void ft_exit(char **str)
{
    if (str[1])
    {
        if (str[2])
        {
            printf("exit\nminishell: exit: too many arguments\n");
            return;
        }
        else if (not_digit(str[1]) == 0)
        {
            printf("exit\n");
            exit(ft_atoi(str[1]) % 256);
        }
        else
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", str[1]);
            exit(255);
        }
    }
    else
    {
        printf("exit\n");
        exit(0);
    }
}
