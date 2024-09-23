/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:58 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/23 00:15:20 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	help_ft_env(t_env **envs)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	add_env(envs, ft_strdup("PATH"),
		ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	add_env(envs, ft_strdup("OLDPWD"), NULL);
	add_env(envs, ft_strdup("PWD"), ft_strdup(cwd));
	add_env(envs, ft_strdup("SHLVL"), ft_strdup("1"));
	add_env(envs, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	free(cwd);
}
