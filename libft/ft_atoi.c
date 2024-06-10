/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:43 by saharchi          #+#    #+#             */
/*   Updated: 2024/02/04 16:04:24 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX_LL 922337203685477580

static int	result(const char *s, int i, int sign)
{
	long long	r;

	r = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (r > MAX_LL)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		r = r * 10 + (s[i] - 48);
		i++;
	}
	return (r);
}

int	ft_atoi(const char *str)
{
	int					i;
	long long			r;
	int					s;

	i = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	r = result(str, i, s);
	return (r * s);
}
