/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:52:33 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/20 11:27:32 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*c;
	size_t	check;

	check = count * size;
	if (count && size && ((check / size) != count))
		return (NULL);
	c = malloc(size * count);
	if (!c)
		exit(1);
	if (!c)
		return (NULL);
	ft_memset(c, 0, count * size);
	return (c);
}
