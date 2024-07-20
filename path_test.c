
#include "minishell.h"

char *get_path(char *cmd, t_env *env)
{
	char *path = NULL;
	char *full_path = NULL;
	char *temp = NULL;
	char *value = NULL;
	char **paths = NULL;

	while (env != NULL)
	{
		if (strcmp(env->key, "PATH") == 0)
		{
			value = strdup(env->value);
			break;
		}
		env = env->next;
	}
	if (value == NULL)
		return NULL;

	paths = ft_split(value, ':');
	free(value);

	for (int i = 0; paths[i] != NULL; i++)
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);

		if (access(full_path, F_OK) != -1)
		{
			for (int j = 0; paths[j] != NULL; j++)
				free(paths[j]);
			return full_path;
		}
		free(full_path);
	}
    for (int j = 0; paths[j] != NULL; j++)
        free(paths[j]);
    free(paths); 
	return NULL;
}

int main()
{
	t_env *env = NULL;
	char *cmd = "cd";
	char *path;

	env = malloc(sizeof(t_env));
	env->key = "PATH";
	env->value = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	env->next = NULL;

	path = get_path(cmd, env);
	if (path != NULL)
	{
		printf("Full path: %s\n", path);
		free(path);
	}
	else
	{
		printf("Command not found\n");
	}

	free(env);

	return 0;
}
