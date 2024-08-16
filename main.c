/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/16 04:09:33 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
	// #include <termios.h>

int main(int ac, char **av, char **env)
{
    char *line;
	t_data *data;
    t_parse *parse;
    (void)ac;
    (void)av;

	data = malloc(sizeof(t_data));
	parse = NULL;
	data->cmd = NULL;
	data->env = NULL;
	if (!env[0])
	{
		data->flag = 1;	
		ft_env(&data->env, env, 1);
	}
	else
		ft_env(&data->env, env, 0);
	rl_catch_signals = 0;
	signal(SIGINT, sighandel);
	signal(SIGQUIT, sighandel);
	g_sigl.sig_child = 0;
    while (1)
    {
		if (!ttyname(0))
			break;
        line = readline("\033[0;34mMinishell$ \033[0;37m");
        if (!line)
            break; 
		parsing(line, data, &parse);
		if (line && *line)
        	add_history(line);

		// t_cmd *tmp = data->cmd;
		// int i = 0;
		// while (tmp)
		// {
		// 	printf("----------------cmd--------------------\n");
		// 	printf("fd_in = %d\n", tmp->fd.fd_in);
		// 	printf("fd_out = %d\n", tmp->fd.fd_out);
		// 	while (tmp->args[i])
		// 	{
		// 		printf("args[%d] = %s\n", i, tmp->args[i]);
		// 		i++;
		// 	}
		// 	i = 0;
		// 	tmp = tmp->next;
		// }
		
		if (data->cmd)
			execute_this(data);
		ft_lstclearcmd(data->cmd);
		data->cmd = NULL;
		ft_lstclear(parse);
        parse = NULL;
        free(line);
	}
	return (0);
}
