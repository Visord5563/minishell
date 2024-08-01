/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:51:06 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/01 06:30:09 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstnewcmd(char **content, t_fd fd)
{
	t_cmd	*list;

	list = malloc(sizeof(t_cmd));
	if (!list)
		return (NULL);
	list->args = content;
	list->fd = fd;
	list->next = NULL;
	return (list);
}

t_cmd	*ft_lstlastcmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_add_backcmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*node;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	node = *cmd;
	node = ft_lstlastcmd(*cmd);
	node->next = new;
}

void	ft_lstclearcmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		ft_free(cmd->args);
		free(cmd);
		cmd = tmp;
	}
}

void	sighandel(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sigl.sig_herdoc == 1)
		{
			g_sigl.sig_herdoc = 0;
			close(0);
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}
