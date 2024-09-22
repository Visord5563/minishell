/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/22 02:11:56 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	init_data(t_data **data, char **env)
{
	*data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	(*data)->cmd = NULL;
	(*data)->env = NULL;
	if (!env[0])
	{
		(*data)->flag = 1;
		ft_env(&(*data)->env, env, 1);
	}
	else
		ft_env(&(*data)->env, env, 0);
}

void	setup_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sighandel);
	signal(SIGQUIT, sighandel);
	g_sigl.sig_child = 0;
}

void	exit_program(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '?'))
		{
			printf("exit");
			exit(ft_atoi(tmp->value));
		}
		tmp = tmp->next;
	}
}

void	command_loop(t_data *data, t_parse *parse)
{
	char			*line;
	struct termios	term;

	while (ttyname(0))
	{
		line = readline("\033[0;34mMinishell$ \033[0;37m");
		if (!line)
			exit_program(data->env);
		if (g_sigl.sig_int == SIGINT)
			exit_status(&data->env, "1");
		parsing(line, data, &parse);
		if (line && *line)
			add_history(line);
		if (data->cmd)
		{
			tcgetattr(0, &term);
			execute_this(data);
			tcsetattr(0, 0, &term);
		}
		ft_lstclearcmd(data->cmd);
		data->cmd = NULL;
		ft_lstclear(parse);
		parse = NULL;
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_parse	*parse;

	(void)ac;
	(void)av;
	parse = NULL;
	init_data(&data, env);
	setup_signals();
	command_loop(data, parse);
	return (0);
}
