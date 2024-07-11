/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:21 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/11 12:08:34 by ehafiane         ###   ########.fr       */
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
// int main() {
//     
//     redirect_output_to_file("output.txt");

//    
//     printf("This will be written to the file 'output.txt'\n");

//     return 0;
// }