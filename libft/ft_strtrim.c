/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:04:16 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/01 03:04:38 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	if (i > j)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[j]) && j > 0)
		j--;
	len = j - i + 1;
	free((char *)s1);
	return (ft_substr(s1, i, len));
}
