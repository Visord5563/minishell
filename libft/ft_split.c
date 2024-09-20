/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:32:37 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/20 11:28:04 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countw(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_free(char **str, int index)
{
	int	i;

	i = 0;
	while (index - i >= 0)
	{
		free(str[index - i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**ft_minisplit(char **str, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = -1;
	while (++k < ft_countw(s, c))
	{
		i = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j + i] != c && s[j + i])
			i++;
		str[k] = ft_substr(s, j, i);
		if (!str[k])
			return (ft_free(str, k));
		j += i;
	}
	str[k] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	char	**p;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_countw(s, c) + 1));
	if (!str)
		exit(1);
	p = ft_minisplit(str, s, c);
	return (p);
}
