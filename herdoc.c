/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:25 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/16 00:28:27 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// Function to emulate heredoc behavior
int heredoc(char *delimiter) 
{

    char *line;
    int fd;
    int fd1;
	char *s;
	
	// s = ft_strjoin("/tmp/.9", ft_itoa((int)delimiter));
    fd = open("/tmp/.97", O_RDWR | O_CREAT | O_TRUNC, 0644);
    fd1 = open("/tmp/.97", O_RDWR);
    unlink("/tmp/.97");
    close(fd);
	// free(s);
    while (1) 
	{
        line = readline("> ");
        if (line == NULL)
            break;
        if (strcmp(line, delimiter) == 0) 
		{
            free(line);
            break;
        }
        ft_putstr_fd(line, fd1);
        free(line);
    }
    return fd1;
}



int main() {
    int fd = heredoc("a");
    // close(fd);
    // fd = open("/tmp/.97", O_RDONLY);
    char *line = malloc(100);
    int i = read(fd, line, 100);
    printf("read %d bytes\n", i);
    ft_putstr_fd(line, 1);
    return 0;
}

