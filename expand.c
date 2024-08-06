/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:41:50 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/06 16:33:57 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_forexp(char c, int i)
{
	if (i == 0 && ((ft_isdigit(c) || ft_isalpha(c) || c == '_' || c == '?')))
		return (1);
	else if (i == 1 && (ft_isdigit(c) || ft_isalpha(c) || c == '_' || c == '?' || c == '"' || c == '\''))
		return (1);
	return (0);
}

char	*return_value(char *str, int i, t_env *envs)
{
	int		j;
	char	*new;
	char	*strtmp;

	j = i + 1;
	new = ft_substr(str, 0, i);
	while (str[j] && check_forexp(str[j], 0))
	{
		if (str[j] == '?')
		{
			j++;
			break ;
		}
		j++;
	}
	strtmp = ft_strjoin(new, check_value(ft_substr(str, i + 1, j - i - 1), envs));
	new = ft_substr(str, j, ft_strlen(str) - j);
	strtmp = ft_strjoin(strtmp, new);
	free(new);
	free(str);
	return (strtmp);
}

char	*expend_str(char *str, t_env *envs)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (str[i])
		{
			if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
				quote = str[i];
			else if (quote == str[i] && (str[i] == '\'' || str[i] == '"'))
				quote = '\0';
			if (str[i] == '$' && ((quote != '\'' && check_forexp(str[i + 1], 0)) || (quote == '\0' && check_forexp(str[i + 1], 1))))
			{
				(1) && (str = return_value(str, i, envs), i--);
			}
			if (ft_strcmp(str, "") == 0)
				return (str);
		}
		if (quote == '\0' && str[i] == '$' && str[i + 1] == '$')
			i += 2;
		else
			i++;
	}
	return (str);
}

void	ft_expend(t_parse **parse, t_env *envs)
{
	t_parse	*tmp;

	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC || tmp->token == RIN || tmp->token == APP || tmp->token == ROUT)
			tmp = tmp->next;
		else if (tmp->token == WORD && ft_strchr(tmp->text, '$'))
		{
				tmp->text = expend_str(tmp->text, envs);
				if (is_space(tmp->text))
					tmp->flag = 1;
		}
		tmp = tmp->next;
	}
}
