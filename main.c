/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/02 00:36:05 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *line;
	t_data *data;
    t_parse *parse;   //termios
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
		if (data->cmd )
			execute_this(data);
		ft_lstclearcmd(data->cmd);
		data->cmd = NULL;
		ft_lstclear(parse);
        parse = NULL;
        free(line);
	}
	return (0);
}
