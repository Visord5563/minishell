/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:44:59 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/14 23:14:09 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(char **str)
{
	int i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	execute_this(t_data *data)
{
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
				exit_status(&data->env, "1");
				exit(EXIT_FAILURE);
			}
		}
		if (if_bultins(cmd_list->args) && flag == 0 && cmd_list->flag == 0)
		{
			handle_redirection(cmd_list);
			check_bultins(cmd_list->args, &data->env);
			dup2(0, 1);
		}
		else if (cmd_list->args[0] && cmd_list->flag == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit_status(&data->env, "1");
				close(fd[0]);
				close(fd[1]);
				break ;
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
					print_command_not_found(cmd_list->args[0], &data->env);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				created_child = 1;
				if((unsigned long)(cmd_index * 4) < sizeof(childpids))
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
		int i = 0;
        while(i < cmd_index)
		{
			if (waitpid(childpids[i], &status, 0) == -1)
				perror("waitpid");
			i++;
		}
		if (status == 256)
			exit_status(&data->env, "127");
		if (status == 3)
		{
			printf("Quit: 3\n");
			exit_status(&data->env, "131");
		}
		g_sigl.sig_child = 0;
	}
	free_all(env);
}

