/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:51:06 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/22 19:39:15 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*ft_lstnewcmd(char **content, t_fd fd, int flag)
{
	t_cmd	*list;

	list = malloc(sizeof(t_cmd));
	if (!list)
		exit(1);
	list->args = content;
	list->fd = fd;
	list->flag = flag;
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
		if (cmd->fd.fd_in > 0)
			close(cmd->fd.fd_in);
		if (cmd->fd.fd_out > 1)
			close(cmd->fd.fd_out);
		free(cmd);
		cmd = tmp;
	}
}

void	sighandel(int sig)
{
	g_sigl.sig_int = sig;
	if (sig == SIGINT)
	{
		if (g_sigl.sig_herdoc == 1)
		{
			g_sigl.sig_herdoc = 0;
			close(0);
		}
		else if (!g_sigl.sig_child)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}
