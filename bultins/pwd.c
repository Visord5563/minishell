/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:15:38 by ehafiane          #+#    #+#             */
/*   Updated: 2024/08/13 10:06:12 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_env *env)
{
	char *old_pwd;
	char *cwd;

	old_pwd = get_oldpwd(env);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
		return (0);
	}
	else
	{
		ft_putendl_fd(old_pwd, 1);
		return (1);
	}
}
