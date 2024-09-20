/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:58:37 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/20 00:23:36 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	help_with_error(t_env **env)
{
	char	*home;

	home = get_home(*env);
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit_status(env, "1");
		return ;
	}
	perror("minishell");
	exit_status(env, "1");
}

void	change_directory(t_env **env, char *home, char *cwd)
{
	char	*tmp;

	if (chdir(home) == -1)
	{
		help_with_error(env);
		return ;
	}
	tmp = set_env(env, "OLDPWD", cwd);
	if (tmp != NULL)
	{
		help_with_error(env);
		free(cwd);
		return ;
	}
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		tmp = set_env(env, "PWD", cwd);
		if (tmp != NULL)
			help_with_error(env);
	}
	else
		help_with_error(env);
	free(cwd);
}

void	home_cd(t_env **env)
{
	char	*home;
	char	*oldpwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell");
		exit_status(env, "1");
		return ;
	}
	home = get_home(*env);
	oldpwd = get_oldpwd(*env);
	if (home)
	{
		change_directory(env, home, cwd);
		exit_status(env, "0");
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit_status(env, "1");
		free(cwd);
	}
}

void	ft_cd(char *arg, t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!arg || strcmp(arg, "~") == 0)
	{
		home_cd(env);
		free(cwd);
		return ;
	}
	if (*arg == '\0')
		return (free(cwd));
	if (chdir(arg) == -1)
	{
		help_with_error(env);
		free(cwd);
	}
	else
		help_cd(env, cwd);
}
