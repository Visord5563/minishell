#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return NULL;
}

size_t ft_strlen(char *s)
{
	size_t i = 0;

	while (s[i])
		i++;
	return i;
}

void ft_strcpy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char *ft_strdup(char *str)
{
	size_t len = ft_strlen(str);
	char *dst = malloc(len + 1);

	if (!dst)
		return 0;
	ft_strcpy(dst, str);
	return dst;
}

char *ft_strjoin(char *s1, char *s2)
{
	size_t s1_len = ft_strlen(s1);
	size_t s2_len = ft_strlen(s2);
	char *join = malloc(s1_len + s2_len + 1);

	if(!s1 || !s2)
		return 0;
	if(!join)
		return 0;
	ft_strcpy(join , s1);
	ft_strcpy((join + s1_len), s2);
	free (s1);
	return (join);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			countread;
	int			to_copy;

	line = ft_strdup(buf);
	while(!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
	{
		buf[countread] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	if (newline)
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
	return line;
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }