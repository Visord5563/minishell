/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/13 22:29:24 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *str, int status)
{
	perror(str);
	exit(status);
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
		ft_putstr_fd("/", 2);
		ft_putstr_fd("is a directory\n", 2);
		exit(126);
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
