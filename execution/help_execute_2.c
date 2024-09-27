/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execute_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:33:00 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/27 00:51:35 by ehafiane         ###   ########.fr       */
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
		check_bultins(cmd_list->args, &data->env, data);
		exit(EXIT_SUCCESS);
	}
	if (data->path != NULL)
	{
		execve(data->path, cmd_list->args, env);
		free(data->path);
	}
	else
		execve(cmd_list->args[0], cmd_list->args, env);
	print_command_not_found(cmd_list->args[0], data);
	exit(EXIT_FAILURE);
}

void	failed_fork(t_data *data, int *fd)
{
	perror("fork");
	exit_status(&data->env, "1");
	close_fd(fd);
}

int	handle_status_update(int status, t_cmd *cmd_list, t_data *data)
{
	char	*tmp;

	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	tmp = ft_itoa(status);
	if (cmd_list->fd.fd_in == -1 || cmd_list->fd.fd_out == -1
		|| cmd_list->fd.fd_in == -2 || cmd_list->fd.fd_out == -2)
		exit_status(&data->env, "1");
	else
		exit_status(&data->env, tmp);
	free(tmp);
	return (status);
}

void	wait_pid_fun(int cmd_index, int *childpids, t_data *data)
{
	int		i;
	int		status;
	int		saved_status;
	t_cmd	*cmd_list;

	i = -1;
	saved_status = 0;
	cmd_list = data->cmd;
	while (++i < cmd_index)
	{
		if (waitpid(childpids[i], &status, 0) == -1)
		{
			perror("waitpid");
		}
		else
		{
			saved_status = handle_status_update(status, cmd_list, data);
		}
		cmd_list = cmd_list->next;
	}
	print_quit(saved_status);
	g_sigl.sig_int = 0;
}
