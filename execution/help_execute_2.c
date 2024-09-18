/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execute_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:33:00 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/18 13:38:52 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	exec_process(t_data *data, t_cmd *cmd_list, int flag)
{
	char	**env;

	env = join_lst(data->env);
	if (if_bultins(cmd_list->args) && flag == 1)
	{
		check_bultins(cmd_list->args, &data->env);
		exit(EXIT_SUCCESS);
	}
	if (data->path != NULL)
	{
		execve(data->path, cmd_list->args, env);
		free(data->path);
	}
	else
		execve(cmd_list->args[0], cmd_list->args, env);
	print_command_not_found(cmd_list->args[0], &data->env);
	exit(EXIT_FAILURE);
}

void	failed_fork(t_data *data, int *fd)
{
	perror("fork");
	exit_status(&data->env, "1");
	close_fd(fd);
}

void	one_bultin(t_data *data, t_cmd *cmd_list)
{
	handle_redirection(cmd_list);
	check_bultins(cmd_list->args, &data->env);
	dup2(0, 1);
}
