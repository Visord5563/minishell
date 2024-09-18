/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:21 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/18 13:32:38 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirect_output_to_file(int file_fd)
{
	if (file_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(file_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(file_fd);
		exit(EXIT_FAILURE);
	}
	close(file_fd);
}

void	redirect_input_from_file(int file_fd)
{
	if (file_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(file_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(file_fd);
		exit(EXIT_FAILURE);
	}
	close(file_fd);
}

void	handle_redirection(t_cmd *cmd)
{
	if (cmd->fd.fd_in > 0)
		redirect_input_from_file(cmd->fd.fd_in);
	if (cmd->fd.fd_out > 1)
		redirect_output_to_file(cmd->fd.fd_out);
}

void	print_quit(t_data *data)
{
	printf("Quit: 3\n");
	exit_status(&data->env, "131");
}

void	initialize_data(t_data *data)
{
	data->cmd_index = 0;
	data->created_child = 0;
	data->temp = 0;
	data->flag_exec = 0;
}
