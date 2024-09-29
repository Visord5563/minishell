/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:45:56 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/25 19:04:45 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "OLDPWD") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*set_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (NULL);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

void	help_cd(t_env **env, char *cwd)
{
	if (cwd)
	{
		if (set_env(env, "OLDPWD", cwd) != NULL)
		{
			help_with_error(env);
			free(cwd);
			return ;
		}
		free(cwd);
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			if (set_env(env, "PWD", cwd) != NULL)
				help_with_error(env);
			free(cwd);
		}
		else
			help_with_error(env);
	}
	else
		ft_putstr_fd("chdir: error retrieving current directory:\
	getcwd: cannot access parent directories: No such file or directory\n", 2);
}

int	check_syntax_export(t_env **env, char *str, int *flag)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		exit_status(env, "1");
		return (*flag = 1, 1);
	}
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status(env, "1");
			return (*flag = 1, 1);
		}
		i++;
	}
	return (0);
}
