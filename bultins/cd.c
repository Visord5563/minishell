/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:58:37 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/24 13:14:31 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void set_env(t_env **env, const char *name, const char *value)
{
    t_env *tmp = *env;
    t_env *prev = NULL;

    while (tmp)
    {
        if (strcmp(tmp->key, name) == 0)
        {
            free(tmp->value);
            tmp->value = strdup(value);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    t_env *new_var = malloc(sizeof(t_env));
    new_var->key = strdup(name);
    new_var->value = strdup(value);
    new_var->next = NULL;

    if (prev)
        prev->next = new_var;
    else
        *env = new_var;
}

char *get_home(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char *get_oldpwd(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, "OLDPWD") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
void ft_cd(char *arg, t_env **env)
{
    char *home;
    char *oldpwd;
    char buffer[4096];
    char *cwd = getcwd(buffer, sizeof(buffer));

    home = get_home(*env);
    oldpwd = get_oldpwd(*env);

    if (!arg || strcmp(arg, "~") == 0)
    {
        if (home)
        {
            if (chdir(home) == -1)
            {
                perror("minishell");
                g_flags.exit_stat = 1;
            }
            else
            {
                set_env(env, "OLDPWD", cwd);
                cwd = getcwd(buffer, sizeof(buffer));
                if (cwd)
                {
                    set_env(env, "PWD", cwd);
                }
            }
        }
        else
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            g_flags.exit_stat = 1;
        }
        return;
    }

    if (strcmp(arg, "-") == 0)
    {
        if (oldpwd)
        {
            if (chdir(oldpwd) == -1)
            {
                perror("minishell");
                g_flags.exit_stat = 1;
            }
            else
            {
                set_env(env, "OLDPWD", cwd);
                cwd = getcwd(buffer, sizeof(buffer));
                if (cwd)
                {
                    set_env(env, "PWD", cwd);
                }
            }
        }
        else
        {
            fprintf(stderr, "minishell: cd: OLDPWD not set\n");
            g_flags.exit_stat = 1;
        }
        return;
    }

    if (chdir(arg) == -1)
    {
        perror("minishell");
        g_flags.exit_stat = 1;
    }
    else
    {
        if (cwd)
        {
            set_env(env, "OLDPWD", cwd);
            cwd = getcwd(buffer, sizeof(buffer));
            if (cwd)
            {
                set_env(env, "PWD", cwd);
            }
        }
    }
}

