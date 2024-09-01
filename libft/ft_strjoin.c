/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:10:05 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/16 04:36:49 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		if (!s1)
			return (ft_strdup(s2));
		else if (!s2)
			return (ft_strdup(s1));
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	nstr = (char *)malloc(sizeof(char) * len);
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(nstr, s2, len);
	free((void *)s1);
	return (nstr);
}
