/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:06:06 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/16 03:19:17 by saharchi         ###   ########.fr       */
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

int	count_str(char *str, char *set)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	quote = '\0';
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_space2(str[i], set))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !is_space2(str[i], set))
			i++;
	}
	return (count);
}

int	ft_strlen2(char *str, char *set)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && !is_space2(str[i], set))
		i++;
	return (i);
}

char	*ft_word(char *str, char *set)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen2(str, set);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**my_split(char *str, char *set)
{
	char	**strings;
	int		i;
	char	quote;

	(1) && (i = 0, quote = '\0');
	strings = (char **)malloc(sizeof(char *) * (count_str(str, set) + 1));
	while (*str != '\0')
	{
		while (*str != '\0' && is_space2(*str, set))
			str++;
		if (*str != '\0')
			strings[i++] = ft_word(str, set);
		while (*str != '\0' && !is_space2(*str, set))
			str++;
	}
	strings[i] = 0;
	return (strings);
}
