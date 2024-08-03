/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:34:16 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/02 04:57:32 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*ft_lstnew(char *content, t_token token)
{
	t_parse	*list;

	list = malloc(sizeof(t_parse));
	if (!list)
		return (NULL);
	list->text = content;
	list->flag = 0;
	list->fd_hdoc = -1;
	list->token = token;
	list->next = NULL;
	return (list);
}

void	ft_lstclear(t_parse *lst)
{
	t_parse	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->text);
		free(lst);
		lst = tmp;
	}
}

void	ft_lstadd_back(t_parse **lst, t_parse *new)
{
	t_parse	*node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = *lst;
	node = ft_lstlast(*lst);
	node->next = new;
}

t_parse	*ft_lstlast(t_parse *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_parse *lst)
{
	t_parse	*newlst;
	int		i;

	if (!lst)
		return (0);
	i = 0;
	newlst = lst;
	while (newlst != NULL)
	{
		i++;
		newlst = newlst->next;
	}
	return (i);
}
