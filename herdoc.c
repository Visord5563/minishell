#include "minishell.h"

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

