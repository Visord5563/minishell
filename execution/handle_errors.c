/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/13 13:18:43 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *str, int status)
{
	perror(str);
	exit(status);
}

void	print_command_not_found(const char *command)
{
	const char	*prefix;
	const char	*suffix;
	size_t		prefix_len;
	size_t		cmd_len;
	size_t		suffix_len;

	prefix_len = strlen(prefix);
	suffix_len = strlen(suffix);
	cmd_len = strlen(command);
	prefix = "minishell: ";
	suffix = ": command not found\n";
	write(STDERR_FILENO, prefix, prefix_len);
	write(STDERR_FILENO, command, cmd_len);
	write(STDERR_FILENO, suffix, suffix_len);
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
