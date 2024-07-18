/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:21 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/13 16:23:47 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void redirect_output_to_file(const char *filename)
 {
	int file_fd;
	
	file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void redirect_input_from_file(const char *filename)
{
	int file_fd;
	
	file_fd = open(filename, O_RDONLY, 0644);
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

void append_output_to_file(const char *filename)
{
    int file_fd;
	 
	file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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


void handle_redirection(t_cmd *cmd)
{
	int i = 0;
	int fd;
	
	while (cmd->args[i])
	{
			if (strcmp(cmd->args[i], ">") == 0)
			{
				redirect_output_to_file(cmd->args[i + 1]);
				for (int j = i + 2; cmd->args[j]; j++)
					cmd->args[j - 2] = cmd->args[j];
				i--;
			}
			else if(strcmp(cmd->args[i], ">>") == 0)
			{
				append_output_to_file(cmd->args[i + 1]);
				for (int j = i + 2; cmd->args[j]; j++)
					cmd->args[j - 2] = cmd->args[j];
				i--;
			}
			else if(strcmp(cmd->args[i], "<") == 0)
			{
				redirect_input_from_file(cmd->args[i + 1]);
				for (int j = i + 2; cmd->args[j]; j++)
					cmd->args[j - 2] = cmd->args[j];
				i--;
			}
		i++;
	}
}
