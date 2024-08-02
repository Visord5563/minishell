/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:21 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/02 00:39:17 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_output_to_file(int file_fd)
{
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

void redirect_input_from_file(int file_fd)
{
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

void handle_redirection(t_cmd *cmd)
{
    if (cmd->fd.fd_in > 0) {
        redirect_input_from_file(cmd->fd.fd_in);
    }
    if (cmd->fd.fd_out > 1) {
        redirect_output_to_file(cmd->fd.fd_out);
    }
}

