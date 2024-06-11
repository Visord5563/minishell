#include "minishell.h"


// Function to emulate heredoc behavior
void heredoc(const char *delimiter) {

    char *line;
    printf("Delimiter = '%s'\n", delimiter);

    while (1) {
        line = readline("> ");
        if (line == NULL) {
            break;
        }
        if (ft_strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        free(line);
    }
}

int main() {
    heredoc("EOF");
    return 0;
}
