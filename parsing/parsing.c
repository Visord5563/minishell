/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:43:24 by saharchi          #+#    #+#             */
/*   Updated: 2024/09/15 11:17:01 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parsing(char *line, t_data *data, t_parse **parse)
{
	parse_line(line, parse, &data->env);
	ft_expand(parse, data->env);
	check_quotes(parse);
	check_heredoc(parse, data->env);
	ft_lstcmd(&data, parse);
}
