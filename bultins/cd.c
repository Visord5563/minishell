/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:58:37 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/16 04:11:56 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

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

char *set_env(t_env **env, char *name, char *value)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*new_var;

	tmp = *env;
	prev = NULL;
	new_var = NULL;
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
	new_var = malloc(sizeof(t_env));
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->key = strdup(name);
	if (!new_var->key)
	{
		free(new_var);
		return (NULL);
	}
	new_var->value = strdup(value);
	if (!new_var->value)
	{
		free(new_var->key);
		free(new_var);
		return (NULL);
	}
	new_var->next = NULL;
	if (prev)
		prev->next = new_var;
	else
		*env = new_var;
	return (NULL);
}

void homd_cd(t_env **env)
{
	char	*home;
	char	*oldpwd;
	char	*cwd;
	char	*tmp;

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
		if (chdir(home) == -1)
		{
			perror("minishell");
			exit_status(env, "1");
		}
		else
		{
			tmp = set_env(env, "OLDPWD", cwd);
			if (tmp != NULL)
			{
				perror("minishell");
				exit_status(env, "1");
				free(cwd);
				return ;
			}
			free(cwd);
			cwd = getcwd(NULL, 0);
			if (cwd)
			{
				tmp = set_env(env, "PWD", cwd);
				if (tmp != NULL)
				{
					perror("minishell");
					exit_status(env, "1");
				}
			}
			else
			{
				perror("minishell");
				exit_status(env, "1");
			}
			free(cwd);
		}
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit_status(env, "1");
	}
}

void ft_cd(char *arg, t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell");
		exit_status(env, "1");
		return ;
	}
	if (!arg || strcmp(arg, "~") == 0)
	{
		homd_cd(env);
		free(cwd);
		return ;
	}
	if (chdir(arg) == -1)
	{
		perror("minishell");
		exit_status(env, "1");
	}
	else
	{
		if (set_env(env, "OLDPWD", cwd) != NULL)
		{
			perror("minishell");
			exit_status(env, "1");
			free(cwd);
			return ;
		}
		free(cwd);
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			if (set_env(env, "PWD", cwd) != NULL)
			{
				perror("minishell");
				exit_status(env, "1");
			}
			free(cwd);
		}
		else
		{
			perror("minishell");
			exit_status(env, "1");
		}
	}
}
