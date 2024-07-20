/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:15:38 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/13 12:49:06 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd()
{
	char pwd[PATH_MAX];
	
	if (getcwd(pwd, PATH_MAX))
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	else
		return (1);
}

// int main()
// {
// 	ft_pwd();
// 	return (0);
// }