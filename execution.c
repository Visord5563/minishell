/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:44:59 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/24 11:19:42 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char *cmd, t_env *env)
{
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
    int fd[2];
    int fd_in = 0;
    char *path = NULL;
    int childpids[256];
    int cmd_index = 0;
    int num_cmds = 0;
    char **env = join_lst(data->env);

    // Count the number of commands
    t_cmd *temp_cmd = data->cmd;
    while (temp_cmd)
    {
        num_cmds++;
        temp_cmd = temp_cmd->next;
    }

    while (data->cmd)
    {
        if (data->cmd->next != NULL && pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Child process
            dup2(fd_in, STDIN_FILENO);
            if (data->cmd->next != NULL)
                dup2(fd[1], STDOUT_FILENO);

            close(fd[0]);
            close(fd[1]);

            handle_redirection(data);

            path = get_path(data->cmd->args[0], data->env);
            if (path != NULL)
            {
                execve(path, data->cmd->args, env);
                free(path);
            }
            else
                execve(data->cmd->args[0], data->cmd->args, env);
            fprintf(stderr, "minishell: %s: command not found\n", data->cmd->args[0]);
            exit(EXIT_FAILURE);
        }
        else
        {
            // parrent process
            childpids[cmd_index++] = pid;
            if (fd_in != 0)
                close(fd_in);
            close(fd[1]);
            fd_in = fd[0];
        }
        data->cmd = data->cmd->next;
    }

    if (fd_in != 0)
        close(fd_in);

    for (int i = 0; i < num_cmds; i++)
    {
        int status;
        if (waitpid(childpids[i], &status, 0) == -1)
        {
            perror("waitpid");
        }
    }

    // Free environment strings
    for (int i = 0; env[i] != NULL; i++)
        free(env[i]);
    free(env);
}

