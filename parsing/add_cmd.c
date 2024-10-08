/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:55 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/20 11:29:01 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_erno(t_parse **parse, int *fd_in, int *fd_out)
{
	ft_putstr_fd("Minishell: ", 2);
	if (*fd_in == -2 || *fd_out == -2)
	{
		ft_putstr_fd((*parse)->next->text, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else
		perror((*parse)->next->text);
}

int	handle_in_ou(t_parse **parse, int *fd_in, int *fd_out, t_data **data)
{
	char	*tmp;
	t_flag	flag;

	flag.flag = 0;
	flag.quote = '\0';
	tmp = (*parse)->next->text;
	if ((*parse)->token == HDOC || (*parse)->token == RIN)
	{
		if (*fd_in != 0)
			close(*fd_in);
		if ((*parse)->token == HDOC)
			*fd_in = (*parse)->fd_hdoc;
		else
			*fd_in = ha_re_in(ft_strdup(tmp), (*data)->env, (*parse)->token);
	}
	else if (((*parse)->token == ROUT || (*parse)->token == APP))
	{
		if (*fd_out != 1)
			close(*fd_out);
		*fd_out = ha_re_ou(ft_strdup(tmp), (*data)->env, (*parse)->token);
	}
	if (*fd_in == -1 || *fd_in == -2 || *fd_out == -1 || *fd_out == -2)
		return (print_erno(parse, fd_in, fd_out), -1);
	return (*parse = (*parse)->next, 0);
}

void	stock_args(char *text, int flag, char ***args, int *j)
{
	int		k;
	char	**str;

	k = 0;
	if ((!ft_strcmp(text, "") && flag != 1) || ft_strcmp(text, ""))
	{
		if (flag != 1 && flag != 2)
			(*args)[(*j)++] = ft_strdup(text);
		else if (flag == 1 || flag == 2)
		{
			str = my_split(text, " \t\n\v\f\r", flag);
			k = 0;
			while (str[k])
			{
				if (flag == 1)
					(*args)[(*j)++] = delete_quotes(str[k++]);
				else
					(*args)[(*j)++] = str[k++];
			}
			free(str);
		}
	}
}

int	add_args(t_parse **parse, char ***args, t_data *data, t_fd *fd)
{
	int		j;
	int		i;
	int		flag;

	(1) && (i = count_args(*parse), flag = 0, j = 0);
	*args = malloc(sizeof(char *) * (i + 1));
	if (!*args)
		exit(1);
	while (*parse && (*parse)->token != PIPE)
	{
		if ((*parse)->token == WORD)
			stock_args((*parse)->text, (*parse)->flag, args, &j);
		else if ((*parse)->token != WORD
			&& (*parse)->token != PIPE && flag == 0)
		{
			if (handle_in_ou(parse, &fd->fd_in, &fd->fd_out, &data) == -1)
			{
				while (*parse && (*parse)->token != PIPE)
					*parse = (*parse)->next;
				return ((*args)[j] = NULL, flag = 1, -1);
			}
		}
		*parse = (*parse)->next;
	}
	return ((*args)[j] = NULL, 0);
}

void	ft_lstcmd(t_data **data, t_parse **parse)
{
	t_fd	fd;
	char	**args;
	t_parse	*tmp;
	int		flag;

	tmp = *parse;
	while (tmp)
	{
		flag = 0;
		fd.fd_in = 0;
		fd.fd_out = 1;
		if (add_args(&tmp, &args, *data, &fd) == -1)
		{
			flag = 1;
			exit_status(&(*data)->env, "1");
		}
		ft_add_backcmd(&(*data)->cmd, ft_lstnewcmd(args, fd, flag));
		if (tmp)
			tmp = tmp->next;
	}
}
