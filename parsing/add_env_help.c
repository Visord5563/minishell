/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:58 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/27 02:23:20 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	help_ft_env(t_env **envs)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	add_env(envs, ft_strdup("PATH"),
		ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	add_env(envs, ft_strdup("OLDPWD"), NULL);
	add_env(envs, ft_strdup("PWD"), ft_strdup(cwd));
	add_env(envs, ft_strdup("SHLVL"), ft_strdup("1"));
	add_env(envs, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	free(cwd);
}

void	check_command(t_cmd *cmd_list)
{
	if (cmd_list->args[0] == NULL && cmd_list->fd.fd_in != -1
		&& cmd_list->fd.fd_out != -1 && cmd_list->fd.fd_in != -2
		&& cmd_list->fd.fd_out != -2)
		exit(0);
	else if (cmd_list->args[0] == NULL || cmd_list->fd.fd_in == -1
		|| cmd_list->fd.fd_out == -1 || cmd_list->fd.fd_in == -2
		|| cmd_list->fd.fd_out == -2)
		exit(1);
}
