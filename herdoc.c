/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:57:25 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/11 11:57:26 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
#include "./libft/libft.h"
#include <fcntl.h>

// Function to emulate heredoc behavior
void heredoc(const char *delimiter) {

    char *line;
    printf("Delimiter = '%s'\n", delimiter);

    chdir("/tmp");
    cd = getcwd(NULL, 0);
    fd = open("herdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1) {
        line = readline("> ");
        if (line == NULL) {
            break;
        }
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        free(line);
    }
}



int main() {
    int fd = heredoc("a");
    close(fd);
    fd = open("herdoc", O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)) != NULL){
        printf("%s", line);
        free(line);
    }
    return 0;
}

