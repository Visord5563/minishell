/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bultins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:21:42 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/14 23:31:49 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_bultins(char **cmd, t_env **env)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd, env);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd[1], env);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(*env);
	else if (ft_strcmp(cmd[0], "env") == 0)
		real_env(*env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(env, cmd);
	else
		return ;
}

int	if_bultins(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}
