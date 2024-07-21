/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:44:59 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/21 12:24:33 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char *cmd, t_env *env)
{
    // char *path = NULL;
    char *full_path = NULL;
    char *temp = NULL;
    char *value = NULL;
    char **paths = NULL;

    while (env != NULL)
    {
        if (strcmp(env->key, "PATH") == 0)
        {
            value = strdup(env->value);
            break;
        }
        env = env->next;
    }
    if (value == NULL)
        return NULL;

    paths = ft_split(value, ':');
    free(value);

    for (int i = 0; paths[i] != NULL; i++)
    {
        temp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);

        if (access(full_path, F_OK) != -1)
        {
            for (int j = 0; paths[j] != NULL; j++)
                free(paths[j]);
            return full_path;
        }
        free(full_path);
    }
    for (int j = 0; paths[j] != NULL; j++)
        free(paths[j]);
    free(paths);
    return NULL;
}


char **join_lst(t_env *env)
{
    char **envp = NULL;
    int i = 0;
    t_env *tmp = env;

    while (tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    envp = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env != NULL)
    {
        envp[i] = ft_strjoin(env->key, "=");
        envp[i] = ft_strjoin(envp[i], env->value);
        env = env->next;
        i++;
    }
    envp[i] = NULL;
    return envp;
}

void execute_this(t_data *data)
{
    pid_t pid;
    int i = 0;
    int fd[2];
    int fd_in = 0;
    char *path = NULL;

    char **env = join_lst(data->env);
    while (data->cmd)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }   
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
            close(fd[0]);
            close(fd[1]);
        }
        if (pid == 0)
        {
            dup2(fd_in, 0);
            if (data->cmd->next)
                dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            handle_redirection(data);
            path = get_path(data->cmd->args[0], data->env);
            execve(data->cmd->args[0], data->cmd->args, env);
            if (path != NULL)
                execve(path, data->cmd->args , env);
            printf("minishell: %s: command not found\n", data->cmd->args[0]);
            exit(EXIT_FAILURE);
        }
        else
        {
            wait(NULL); 
            close(fd[1]);
            fd_in = fd[0];
            i++;
        }

        data->cmd = data->cmd->next;
        
    }
    close(fd_in); 
}