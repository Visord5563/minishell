/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:41:50 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/10 23:54:08 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *text)
{
	ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("'\n", 2);
}

int	ch_fexp(char c, int i, int j)
{
	if (i == 0 && ((ft_isdigit(c) || ft_isalpha(c) || c == '_' || c == '?')))
		return (1);
	else if (i == 1 && (j % 2 != 0) && (ft_isdigit(c) || ft_isalpha(c)
			|| c == '_' || c == '?' || c == '"' || c == '\''))
		return (1);
	return (0);
}

char	*return_value(char *str, int i, t_env *envs, int flag)
{
	int		j;
	char	*new;
	char	*strtmp;

	j = i + 1;
	new = ft_substr(str, 0, i);
	while (str[j] && ch_fexp(str[j], 0, 0))
	{
		if (str[j] == '?')
		{
			j++;
			break ;
		}
		j++;
	}
	strtmp = ft_strjoin(new, check_value(ft_substr(str, i + 1, j - i - 1),
				envs, flag));
	new = ft_substr(str, j, ft_strlen(str) - j);
	strtmp = ft_strjoin(strtmp, new);
	free(new);
	free(str);
	return (strtmp);
}

char	*expand_str(char *str, t_env *envs, int flag)
{
	int		i;
	int		j;
	char	quote;

	(1) && (i = 0, j = 0, quote = '\0');
	while (str[i])
	{
		j++;
		if (str[i] != '$')
			j = 0;
		if (str[i])
		{
			if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
				quote = str[i];
			else if (quote == str[i] && (str[i] == '\'' || str[i] == '"'))
				quote = '\0';
			if (str[i] == '$' && ((quote != '\'' && ch_fexp(str[i + 1], 0, 0))
					|| (quote == '\0' && ch_fexp(str[i + 1], 1, j))))
				(1) && (str = return_value(str, i, envs, flag), i--);
			if (ft_strcmp(str, "") == 0)
				return (str);
		}
		i++;
	}
	return (str);
}

void	ft_expand(t_parse **parse, t_env *envs)
{
	t_parse	*tmp;
	int flag = 0;

	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC || tmp->token == RIN
			|| tmp->token == APP || tmp->token == ROUT)
			tmp = tmp->next;
		else if (tmp->token == WORD && ft_strchr(tmp->text, '$'))
		{
			tmp->text = expand_str(tmp->text, envs, flag);
			if (is_space(tmp->text) || ft_strcmp(tmp->text, "") == 0)
				tmp->flag = 1;
		}
		if (tmp->token == PIPE)
			flag = 1;
		tmp = tmp->next;
	}
}
