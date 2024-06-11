/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:46:17 by saharchi          #+#    #+#             */
/*   Updated: 2024/06/11 10:58:58 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*s1;
	unsigned char	t;

	t = (unsigned char)c;
	s1 = (char *)s;
	if (t == '\0')
		return (&s1[ft_strlen(s)]);
	while (*s1)
	{
		if (t == *s1)
			return (s1);
		s1++;
	}
	return (0);
}
