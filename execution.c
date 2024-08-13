/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:44:59 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/13 02:05:54 by saharchi         ###   ########.fr       */
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
        if (access(full_path, F_OK) != -1)
            return full_path;
        free(full_path);
    }
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
        envp[i] = ft_strjoin(ft_strdup(env->key), "=");
        envp[i] = ft_strjoin(envp[i], env->value);
        env = env->next;
        i++;
    }
    envp[i] = NULL;
    return envp;
}

void execute_this(t_data *data)
{
    // puts("bsmllllllllllah");
    pid_t pid;
    int fd[2];
    int fd_in = 0;
    char *path = NULL;
    int status;
    int cmd_index = 0;
    int num_cmds = 0;
    int childpids[256];
    int created_child = 0;
    int flag = 0;

    char **env = join_lst(data->env);
    t_cmd *cmd_list = data->cmd;
    t_cmd *tmp_cmd_list = cmd_list;
    while (tmp_cmd_list)
    {
        num_cmds++;
        tmp_cmd_list = tmp_cmd_list->next;
    }
    while (cmd_list)
    {
        if (cmd_list->next)
        {
            flag = 1;
            if (pipe(fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        if (if_bultins(cmd_list->args) && flag == 0)
        {
            handle_redirection(cmd_list);
            check_bultins(cmd_list->args, &data->env);
            dup2(0, 1);
            // break; 
        }
        else
        {
            pid = fork();
            if (pid < 0)
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid == 0)
            {
                dup2(fd_in, 0); 
                if (cmd_list->next)
                {
                    dup2(fd[1], 1); 
                    close(fd[0]);
                    close(fd[1]);
                }
                handle_redirection(cmd_list);
                path = get_path(cmd_list->args[0], data->env);
                if (cmd_list->args[0])
                {
                if (if_bultins(cmd_list->args) && flag == 1)
                {
                    check_bultins(cmd_list->args, &data->env);
                    exit(EXIT_SUCCESS); 
                }
                    if (path != NULL)
                    {
                        execve(path, cmd_list->args, env);
                        free(path);
                    }
                    else
                        execve(cmd_list->args[0], cmd_list->args, env);
                    print_command_not_found(cmd_list->args[0]);
                    exit(EXIT_FAILURE);
                }
                // else
                // {
                //     exit(EXIT_FAILURE);
                // }
            }
            else
            {
                created_child = 1;
                childpids[cmd_index++] = pid;
                if (fd_in != 0)
                    close(fd_in);

                if (cmd_list->next)
                    close(fd[1]);
                fd_in = fd[0];
            }
        }
        cmd_list = cmd_list->next;
    }
    if (fd_in != 0)
        close(fd_in);
    if (created_child)
    {
        g_sigl.sig_child = 1;
        for (int i = 0; i < cmd_index; i++)
            if (waitpid(childpids[i], &status, 0) == -1)
                perror("waitpid");
        if (status == 3)
            printf("Quit: 3\n");
        g_sigl.sig_child = 0;
    }

    free(env);
}
