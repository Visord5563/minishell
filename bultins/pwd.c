/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:15:38 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/24 11:52:47 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd()
{
    char pwd[PATH_MAX];

    if (getcwd(pwd, PATH_MAX))
    {
        ft_putendl_fd(pwd, 1);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1);
    }
}