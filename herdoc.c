#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

size_t ft_strlen(const char *s) {
    size_t i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}


void	ft_strcpy(char *dst, const char *src)
{
	while (*src)	
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strdup(const char *src)
{
	size_t	len = ft_strlen(src) + 1;
	char	*dst = malloc(len);
	
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	s1_len = ft_strlen(s1);
	size_t	s2_len = ft_strlen(s2);
	char	*join = malloc((s1_len + s2_len + 1));

	if (!s1 || !s2)
		return (NULL);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy((join + s1_len), s2);
	free(s1);
	return (join);
}

char	*get_next_line(int fd)
{
	static char	buf[50 + 1];
	char		*line;
	char		*newline;
	int			countread;
	int			to_copy;

	line = ft_strdup(buf);
	while (!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, 50)))
	{
		buf[countread] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		buf[0] = '\0';
	}
	line[to_copy] = '\0';
	return (line);
}

int heredoc(const char *delimiter) {

    char *line;
    int fd;
    char *cd;

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
        line = ft_strjoin(line, "\n");
        write(fd, line, ft_strlen(line));
        free(line);
    }
    chdir(cd);
    return fd;
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
