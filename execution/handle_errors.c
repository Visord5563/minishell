/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/22 22:53:57 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *str, int status)
{
	perror(str);
	exit(status);
}

int	check_for_bs(t_env *env)
{
	t_env *tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
		{
			return 0;	
		}
		tmp = tmp->next;
	}
	return 1;
}


void print_command_not_found(char *command, t_data *data) {
    char *prefix = "minishell: ";
    char *suffix = ": command not found\n";
    struct stat buf;

	ft_putstr_fd(prefix, 2);
    stat(command, &buf);
	if(ft_strchr(command , '/'))
	{
        if (S_ISDIR(buf.st_mode))
		{
            ft_putstr_fd(command, 2);
            ft_putstr_fd(": is a directory\n", 2);
            exit(126);
        }
		perror(command);
		if (errno == 13 || errno == 20)
			exit(126);
		if (errno == 2)
			exit(127);
    }
	if (check_for_bs(data->env) == 1)
	{
		if (!ft_strcmp(command , "..") || !ft_strcmp(command , "."))
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
		perror(command);
		if (errno == 13)
			exit(126);
		exit(127);
	}
    ft_putstr_fd(command, 2);
    ft_putstr_fd(suffix, 2);
    exit(127);
}

void	env_key_error(char **cmd, t_env **env, int i, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	exit_status(env, "1");
}

void	pipe_error(t_data *data, int *fd, int *flag)
{
	*flag = 1;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit_status(&data->env, "1");
		exit(EXIT_FAILURE);
	}
}
