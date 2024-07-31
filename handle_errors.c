/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:52:23 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/31 18:02:08 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_error(char *str, int status)
{
	perror(str);
	exit(status);
}

void print_command_not_found(const char *command)
{
    const char *prefix = "minishell: ";
    const char *suffix = ": command not found\n";
    size_t prefix_len = strlen(prefix);
    size_t cmd_len = strlen(command);
    size_t suffix_len = strlen(suffix);

    write(STDERR_FILENO, prefix, prefix_len);
    write(STDERR_FILENO, command, cmd_len);
    write(STDERR_FILENO, suffix, suffix_len);
}
