#include "minishell.h"


// Function to emulate heredoc behavior
void heredoc(const char *delimiter) {
    char *line;
    FILE *tempFile = tmpfile();

    printf("Delimiter = '%s'\n", delimiter);

    while (1) {
        line = readline("> ");
        if (line == NULL) {
            break;
        }
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        fputs(line, tempFile); 
        fputs("\n", tempFile); 
        free(line);
    }
    fclose(tempFile);
}

int main() {
    heredoc("EOF");
    return 0;
}

