/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:41:50 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/21 11:18:06 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	count_forexp(char *str, int j)
{
	while (str[j] && ch_fexp(str[j], 0, 0))
	{
		if (str[j] == '?')
		{
			j++;
			break ;
		}
		j++;
	}
	return (j);
}

char	*add_quot(char *value, int *flag1, char quote)
{
	if (ft_strchr(value, '\'') && quote != '"')
	{
		*flag1 = 1;
		value = ft_strjoin(ft_strdup("\""), value);
		value = ft_strjoin(value, "\"");
	}
	else if (ft_strchr(value, '"') && quote != '"')
	{
		*flag1 = 1;
		value = ft_strjoin(ft_strdup("\'"), value);
		value = ft_strjoin(value, "\'");
	}
	else if (ft_strchr(value, '"') && quote == '"')
	{
		*flag1 = 1;
		value = ft_strjoin(ft_strdup("\"\'"), value);
		value = ft_strjoin(value, "\'\"");
	}
	return (value);
}

char	*return_value(char *str, int i, t_env *envs, t_flag *flag)
{
	int		j;
	char	*new;
	char	*strtmp;
	char	*value;

	new = ft_substr(str, 0, i);
	strtmp = ft_strdup("");
	j = count_forexp(str, i + 1);
	value = check_value(ft_substr(str, i + 1, j - i - 1), envs, flag->flag);
	if (value)
	{
		value = add_quot(value, &flag->flag1, flag->quote);
		free(strtmp);
		strtmp = ft_strjoin(new, value);
		char *s = ft_strdup(str);
		new = ft_substr(s, j, ft_strlen(str) - j);
		free(s);
		free(new);
		strtmp = ft_strjoin(strtmp, new);
	}
	if (!value)
		free(new);
	free(str);
	return (strtmp);
}

char	*expand_str(char *str, t_env *envs, t_flag *flag)
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

char	is_quote(char *text)
{
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	while (text[j] && text[j] != '$')
	{
	if (quote == '\0' && text[j] == '"')
		quote = text[j];
	else if (text[j] == quote)
		quote = '\0';
	j++;
	}
	return (quote);
}

int	count_quotes(char *text)
{
	int i = 0;
	int j = 0;
	while(text[i])
	{
		if (text[i] == '"')
			j++;
		if (j && text[i] != '"')
			break;
		i++;
	}
	return (j);
}

void	git_expand(t_flag flag, t_parse *tmp, char *str, t_env *envs)
{
	int		j;

	flag.flag1 = 0;
	flag.quote = is_quote(tmp->text);
	tmp->text = expand_str(tmp->text, envs, &flag);
	j = count_quotes(tmp->text);
	if ((is_space(tmp->text) && ft_strcmp(str, "export")
		&& (j % 2 == 0)) || ft_strcmp(tmp->text, "") == 0
		|| (is_space(tmp->text) && ft_strcmp(str, "export") && flag.flag1 == 1))
		tmp->flag = 1;
}

void	ft_expand(t_parse **parse, t_env *envs)
{
	t_flag	flag;
	t_parse	*tmp;
	char	*str;

	flag.flag = 0;
	tmp = *parse;
	str = ft_strdup("");
	while (tmp)
	{
		if (tmp->token == WORD && ft_strcmp(tmp->text, "export") && tmp->next)
			str = ft_strdup(tmp->text);
		if (tmp->token == HDOC || tmp->token == RIN
			|| tmp->token == APP || tmp->token == ROUT)
			tmp = tmp->next;
		else if (tmp->token == WORD && ft_strchr(tmp->text, '$'))
			git_expand(flag, tmp, str, envs);
		free(str);
		if (tmp->token == PIPE)
			flag.flag = 1;
		str = ft_strdup(tmp->text);
		tmp = tmp->next;
	}
	free(str);
}