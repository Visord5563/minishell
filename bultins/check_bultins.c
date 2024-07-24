/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bultins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:21:42 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/24 09:52:23 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_bultins(char **cmd, t_env *env)
{
	(void)env;
    if (strcmp(cmd[0], "echo") == 0)
        ft_echo(cmd);
    else if (strcmp(cmd[0], "cd") == 0)
        ft_cd(cmd[1]);
    else if (strcmp(cmd[0], "pwd") == 0)
        ft_pwd();
    else if (strcmp(cmd[0], "exit") == 0)
        ft_exit(cmd);
    else
        return;
}

int if_bultins(char **cmd)
{
	if (strcmp(cmd[0], "echo") == 0)
		return 1;
	else if (strcmp(cmd[0], "cd") == 0)
		return 1;
	else if (strcmp(cmd[0], "pwd") == 0)
		return 1;
	else if (strcmp(cmd[0], "exit") == 0)
		return 1;
	else
		return 0;
}