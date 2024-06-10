/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:29:04 by saharchi          #+#    #+#             */
/*   Updated: 2023/11/24 20:47:11 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *f, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*f == '\0')
		return ((char *)s);
	while (i + j < len && s[i])
	{
		j = 0;
		while (s[i + j] == f[j] && i + j < len)
		{
			j++;
			if (f[j] == '\0')
				return ((char *)(s + i));
		}
		i++;
	}
	return (NULL);
}
