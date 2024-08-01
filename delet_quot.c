/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delet_quot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:46:50 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/27 20:14:45 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_espace(char *str)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == '\0')
			break ;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*delete_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	char	quote;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i++];
			if (quote != str[i])
				new[j++] = str[i++];
		}
		else if (str[i] == quote)
			(1) && (quote = '\0', i++);
		else
			new[j++] = str[i++];
	}
	return (free(str), new[j] = '\0', new);
}

void	check_quotes(t_parse **parse)
{
	t_parse	*tmp;

	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC || tmp->flag == 1)
			tmp = tmp->next;
		else if (tmp->text)
		{
			if (ft_strchr(tmp->text, '\'') || ft_strchr(tmp->text, '"'))
				tmp->text = delete_quotes(tmp->text);
		}
		if (tmp)
			tmp = tmp->next;
	}
}
