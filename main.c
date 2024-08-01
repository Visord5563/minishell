/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/02 00:19:22 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_env(&data->env, env);
	rl_catch_signals = 0;
	signal(SIGINT, sighandel);
	signal(SIGQUIT, sighandel);
    while (1)
    {
        line = readline("\033[0;34mMinishell$ \033[0;37m");
        if (!line)
            break; 
        parse_line(line, &parse, &data->env);
		ft_expend(&parse, data->env);
		check_quotes(&parse);
		check_heredoc(&parse, data->env);
		ft_lstcmd(&data, &parse);
		if (line && *line)
        	add_history(line);
		t_cmd *tmp = data->cmd;
		int i ;
		while (tmp)
		{
			printf("----------------cmd--------------------\n");
			printf("fd_in = %d\n", tmp->fd.fd_in);
			printf("fd_out = %d\n", tmp->fd.fd_out);
			i = 0;
			while (tmp->args[i])
			{
				printf("args[%d] = %s\n", i, tmp->args[i]);
				i++;
			}
			tmp = tmp->next;
		}
		// if((data->cmd) && if_bultins(data->cmd->args))
		// {
		// 	check_bultins(data->cmd->args, &data->env);
		// 	// printf("bultins\n");
		// }
		// else if (data->cmd )
		// {
		// 	// printf("execute\n");
		// 	// printf("execute\n");
		// 	execute_this(data);
		// }
		ft_lstclearcmd(data->cmd);
		data->cmd = NULL;
		ft_lstclear(parse);
		parse = NULL;
        free(line);
	}
	return (0);
}
