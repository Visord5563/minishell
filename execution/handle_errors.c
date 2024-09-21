/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/21 10:52:51 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *str, int status)
{
	perror(str);
	exit(status);
}

int	check_for_bs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/')
			return (1);
		i++;
	}
	return (0);
}

void	print_command_not_found(char *command, t_env **env)
{
	char	*prefix;
	char	*suffix;

	(void)env;
	prefix = "minishell: ";
	suffix = ": command not found\n";
	if (ft_strchr(command, '/'))
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": No such file or directory \n", 2);
		exit(127);
	}
	ft_putstr_fd(prefix, 2);
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
