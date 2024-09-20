/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:06:06 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/20 11:30:29 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_space2(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	cont_str_nonq(char *str, char *set, int i, char *quote)
{
	while (str[i] != '\0')
	{
		if (*quote == '\0' && (str[i] == '"' || str[i] == '\''))
			*quote = str[i];
		else if (str[i] == *quote)
			*quote = '\0';
		else if (*quote == '\0' && ft_strchr(set, str[i]))
			break ;
		i++;
	}
	return (i);
}

char	*ft_word(char *str, char *set, int flag)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	if (flag == 1)
		len_word = ft_strlen2(str, set);
	else
		len_word = ft_strlen1(str, set);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		exit(1);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	count_nonq(char **str, char *set, char *quote)
{
	while (**str != '\0')
	{
		if (*quote == '\0' && (**str == '"' || **str == '\''))
			*quote = **str;
		else if (**str == *quote)
			*quote = '\0';
		else if (*quote == '\0' && ft_strchr(set, **str))
			break ;
		(*str)++;
	}
}

char	**my_split(char *str, char *set, int flag)
{
	char	**strings;
	int		i;
	char	quote;

	(1) && (i = 0, quote = '\0');
	strings = (char **)malloc(sizeof(char *) * (count_str(str, set, flag) + 1));
	if (!strings)
		exit(1);
	while (*str != '\0')
	{
		while (*str != '\0' && is_space2(*str, set))
			str++;
		if (*str != '\0')
			strings[i++] = ft_word(str, set, flag);
		if (flag == 1)
			count_nonq(&str, set, &quote);
		else
			while (*str != '\0' && !is_space2(*str, set))
				str++;
	}
	strings[i] = NULL;
	return (strings);
}
