/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_execute_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:21:27 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/27 00:48:10 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	one_bultin(t_data *data, t_cmd *cmd_list)
{
	handle_redirection(cmd_list);
	check_bultins(cmd_list->args, &data->env, data);
	dup2(0, 1);
}

void	wait_this(t_data *data, int num_cmds)
{
	if (data->created_child)
	{
		g_sigl.sig_child = 1;
		wait_pid_fun(num_cmds, data->childpids, data);
		g_sigl.sig_child = 0;
	}
}
