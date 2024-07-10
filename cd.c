/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:58:37 by ehafiane          #+#    #+#             */
/*   Updated: 2024/07/10 16:53:10 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
		return (1);
	}
	// ft_pwd();
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	ft_cd(argv[1]);
	return (0);
}