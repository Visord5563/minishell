/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:05:34 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/20 16:20:21 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*retrieve_path_value(t_env *env)
{
	char	*value;

	value = NULL;
	while (env != NULL)
	{
		if (strcmp(env->key, "PATH") == 0)
		{
			value = strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (value);
}

static char	*find_command_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	full_path = NULL;
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
	return (NULL);
}

char	*get_path(char *cmd, t_env *env)
{
	char	*value;
	char	**paths;
	char	*full_path;

	value = retrieve_path_value(env);
	if (value == NULL)
		return (NULL);
	paths = ft_split(value, ':');
	free(value);
	if (paths == NULL)
		return (NULL);
	full_path = find_command_in_paths(cmd, paths);
	return (full_path);
}

char	**join_lst(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*tmp;

	tmp = env;
	envp = NULL;
	i = 0;
	while (tmp != NULL)
		(1) && (i++, tmp = tmp->next);
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		exit(1);
	i = 0;
	while (env != NULL)
	{
		if (env->value)
		{
			envp[i] = ft_strjoin(ft_strdup(env->key), "=");
			envp[i] = ft_strjoin(envp[i], env->value);
			i++;
		}
		env = env->next;
	}
	return (envp[i] = NULL, envp);
}

void	wait_pid_fun(int cmd_index, int *childpids, t_data *data)
{
	int		i;
	int		status;
	char	*tmp;

	i = -1;
	while (++i < cmd_index)
	{
		if (waitpid(childpids[i], &status, 0) == -1)
			perror("waitpid");
		else
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				status = WTERMSIG(status) + 128;
				if (status == 131 || status == 130)
					print_quit(status, data);
			}
			tmp = ft_itoa(status);
			exit_status(&data->env, tmp);
			free(tmp);
		}
	}
	g_sigl.sig_int = 0;
}
