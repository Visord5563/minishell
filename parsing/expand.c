/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:41:50 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/20 10:20:15 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*return_value(char *str, int i, t_env *envs, t_flag *flag)
{
	int		j;
	char	*new;
	char	*strtmp;
	char	*value;

	j = count_forexp(str, i + 1);
	new = ft_substr(str, 0, i);
	value = check_value(ft_substr(str, i + 1, j - i - 1), envs, flag->flag);
	if (value)
		value = add_quot(value, flag->quote);
	strtmp = ft_strjoin(new, value);
	if (value[0] != '\0')
		free(value);
	if (!value)
		free(new);
	new = ft_substr(str, j, ft_strlen(str) - j);
	strtmp = ft_strjoin(strtmp, new);
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
		if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote == str[i] && (str[i] == '\'' || str[i] == '"'))
			quote = '\0';
		if (str[i] == '$' && (j % 2 != 0)
			&& ((quote != '\'' && ch_fexp(str[i + 1], 0))
				|| (quote == '\0' && ch_fexp(str[i + 1], 1))))
			(1) && (str = return_value(str, i, envs, flag), i--);
		if (ft_strcmp(str, "") == 0)
			return (str);
		i++;
	}
	return (str);
}

int	check_fsplit(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			j = 1;
		if (str[i] == '=' && j == 1)
			return (1);
		i++;
	}
	return (0);
}

void	git_expand(t_flag flag, t_parse *tmp, char *str, t_env *envs)
{
	int		j;
	int		i;

	flag.quote = is_quote(tmp->text);
	i = check_fsplit(tmp->text);
	j = count_quotes(tmp->text);
	tmp->text = expand_str(tmp->text, envs, &flag);
	if ((is_space(tmp->text) && ft_strcmp(str, "export") && (j % 2 == 0))
		|| ft_strcmp(tmp->text, "") == 0)
		tmp->flag = 2;
	else if ((is_space(tmp->text) && !ft_strcmp(str, "export")) && i == 1)
		tmp->flag = 1;
}

void	ft_expand(t_parse **parse, t_env *envs)
{
	t_flag	flag;
	t_parse	*tmp;
	char	*str;

	(1) && (flag.flag = 0, tmp = *parse, str = ft_strdup(""));
	while (tmp)
	{
		if (tmp->token == WORD && ft_strcmp(tmp->text, "export") == 0
			&& tmp->next)
		{
			free(str);
			str = ft_strdup(tmp->text);
		}
		if (tmp->token == HDOC || tmp->token == RIN
			|| tmp->token == APP || tmp->token == ROUT)
			tmp = tmp->next;
		else if (tmp->token == WORD && ft_strchr(tmp->text, '$'))
			git_expand(flag, tmp, str, envs);
		if (tmp->token == PIPE)
			flag.flag = 1;
		free(str);
		str = ft_strdup(tmp->text);
		tmp = tmp->next;
	}
	free(str);
}
