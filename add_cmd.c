/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:55 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/01 22:41:25 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_expend(t_env *env, char *str)
{
	int fd;
	char	*tmp;
	
	fd = 0;
	tmp = expend_str(ft_strdup(str), env);
	if (is_space(tmp)  || ft_strcmp(tmp, "") == 0)
	{
		tmp = ft_strtrim(tmp, " \t\n\v\f\r");
		if (is_space(tmp)  || ft_strcmp(tmp, "") == 0)
			fd = -2;
	}
	if(fd != -2)
		fd = open(tmp, O_RDONLY, 0644);
	free(tmp);
	return (fd);
}

int	ha_re_in(char *file, t_env *env)
{
	int	fd;

	if (ft_strchr(file, '$'))
	{
		fd = handle_expend(env, file);
		return (fd);
	}
	if (!ft_strcmp(file, ""))
		return (-2);
	fd = open(file, O_RDONLY, 0644);
	// free(file);
	return (fd);
}

int	ha_re_ou(char *file, t_env *env, int token)
{
	int	fd;
	if (ft_strchr(file, '$'))
	{
		fd = handle_expend(env, file);
		return (fd);
	}
	if (token == ROUT)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0764);
	else
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0764);
	// free(file);
	return (fd);
}

int	handle_in_ou(t_parse **parse, int *fd_in, int *fd_out, t_data **data)
{
	char	*tmp;
	
	tmp = (*parse)->next->text;
	if ((*parse)->token == HDOC || (*parse)->token == RIN)
	{
		if (*fd_in != 0)
			close(*fd_in);
		if ((*parse)->token == HDOC)
			*fd_in = (*parse)->fd_hdoc;
		else
			*fd_in = ha_re_in(tmp, (*data)->env);
	}
	else if (((*parse)->token == ROUT || (*parse)->token == APP))
	{
		if (*fd_out != 1)
			close(*fd_out);
		*fd_out = ha_re_ou(tmp, (*data)->env, (*parse)->token);
	}
	if (*fd_in == -1 || *fd_in == -2 || *fd_out == -1 || *fd_out == -2)
	{
		if (*fd_in == -2 || *fd_out == -2)
		{
			ft_putstr_fd((*parse)->next->text, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
		}
		else
			perror((*parse)->next->text);
		return (-1);
	}
	return (*parse = (*parse)->next, 0);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int add_args(t_parse **parse, char ***args, t_data *data, t_fd *fd) 
{
    int j;
    int i;
	int k;
	char **str;

	(void)data;
	(void)fd;
    i = count_args(*parse);
    *args = malloc(sizeof(char *) * (i + 1));
    if (!*args)
        return (-1);
    j = 0;
    while (*parse && (*parse)->token != PIPE) 
	{
        if ((*parse)->token == WORD) 
		{
            if (ft_strcmp((*parse)->text, ""))
			{
				if((*parse)->flag != 1)
                	(*args)[j++] = ft_strdup((*parse)->text);
				else
				{
					str = my_split((*parse)->text, " \t\n\v\f\r");
					k = 0;
					while (str[k])
						(*args)[j++] = delete_quotes(str[k++]);
					// ft_free(str);
				}
			}
        } 
		else if ((*parse)->token == HDOC || (*parse)->token == RIN || (*parse)->token == ROUT || (*parse)->token == APP)
            if (handle_in_ou(parse, &fd->fd_in, &fd->fd_out, &data) == -1)
			{
				if (i > 0)
				{
					(*args)[j] = NULL;
				}
                return (-1);
			}
        *parse = (*parse)->next;
    }
    (*args)[j] = NULL;
	return (0);
}

void ft_lstcmd(t_data **data, t_parse **parse) 
{
    t_fd fd;
    char **args;

	fd.fd_in = 0;
	fd.fd_out = 1;
	t_parse *tmp = *parse;
	while (tmp)
	{
		if (add_args(&tmp, &args, *data, &fd) == -1)
		{
			ft_lstclearcmd((*data)->cmd);
			ft_free(args);
			(*data)->cmd = NULL;
			break;
		}
		ft_add_backcmd(&(*data)->cmd, ft_lstnewcmd(args, fd));
		if (tmp)
			tmp = tmp->next;
	}
}