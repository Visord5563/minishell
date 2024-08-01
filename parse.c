/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:44:37 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/01 07:03:20 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != '<' && c != '>' && c != '|' )
		return (0);
	return (1);
}

void	check_token(t_parse **parse, char *line, int *i)
{
	if (line[*i] == '|')
		ft_lstadd_back(parse, ft_lstnew(ft_strdup("|"), PIPE));
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ft_lstadd_back(parse, ft_lstnew(ft_strdup("<<"), HDOC));
		(*i)++;
	}
	else if (line[*i] == '<')
		ft_lstadd_back(parse, ft_lstnew(ft_strdup("<"), RIN));
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		ft_lstadd_back(parse, ft_lstnew(ft_strdup(">>"), APP));
		(*i)++;
	}
	else
		ft_lstadd_back(parse, ft_lstnew(ft_strdup(">"), ROUT));
	(*i)++;
}

int	check_syntax(t_parse **parse)
{
	t_parse	*tmp;

	tmp = *parse;
	if (tmp && tmp->token == PIPE)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
		{
			printf("Minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		else if ((tmp->token == RIN || tmp->token == ROUT || tmp->token == APP
				|| tmp->token == HDOC)
			&& (!tmp->next || (tmp->next->token != WORD)))
		{
			if (!tmp->next)
				printf("Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	str_len(char *line, int i, char *quote)
{
	int	j;

	j = i;
	while (line[j])
	{
		if (*quote == '\0' && (line[j] == '"' || line[j] == '\''))
			*quote = line[j];
		else if (line[j] == *quote)
			*quote = '\0';
		else if (*quote == '\0' && (check(line[j])))
			break ;
		j++;
	}
	return (j);
}

void exit_status(t_env **env, char *status)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if (!ft_strcmp(tmp->key, "?"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(status);
			return ;
		}
		tmp = tmp->next;
	}
}

void	parse_line(char *line, t_parse **parse, t_env **env)
{
	int		i;
	int		j;
	char	quote;

	(void)env;
	i = 0;
	quote = '\0';
	while (line[i])
	{
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			check_token(parse, line, &i);
		else if (line[i] != '\0')
		{
			(1) && (j = i, i = str_len(line, i, &quote));
			ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), 0));
		}
	}
	if (quote != '\0' || check_syntax(parse) == 1)
	{
		if (quote != '\0')
			printf("Minishell: syntax error near unexpected token `%c'\n", quote);
		exit_status(env, "258");
		(1) && (ft_lstclear(*parse), *parse = NULL);
		return ;
	}
}
