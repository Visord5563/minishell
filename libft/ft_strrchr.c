/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:42:58 by saharchi          #+#    #+#             */
/*   Updated: 2023/11/10 02:10:16 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*s1;
	char	t;

	s1 = (char *) s;
	t = (char) c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s1[i] == t)
			return (s1 + i);
		i--;
	}
	return (NULL);
}
