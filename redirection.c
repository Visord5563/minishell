/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:21 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/27 23:38:18 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void redirect_output_to_file(t_data *data)
 {
	int file_fd;
	
	file_fd = data->cmd->fd->fd_out;
	if (file_fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(file_fd, STDOUT_FILENO) < 0) {
		perror("dup2");
		close(file_fd);
		exit(EXIT_FAILURE);
	}
	close(file_fd);
}

void redirect_input_from_file(t_data *data)
{
	int file_fd;

	printf("data->cmd->fd->fd_in = %d\n", data->cmd->fd->fd_in);
	file_fd = data->cmd->fd->fd_in;
	if (file_fd < 0) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(file_fd, STDIN_FILENO) < 0) {
		perror("dup2");
		close(file_fd);
		exit(EXIT_FAILURE);
	}
	close(file_fd);
}

void handle_redirection(t_data *data)
{

	if (data->cmd->fd->fd_in > 0)
		redirect_input_from_file(data);
	if (data->cmd->fd->fd_out > 1)
		redirect_output_to_file(data);
}
