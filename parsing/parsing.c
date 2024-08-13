/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 03:43:24 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/13 03:44:07 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parsing(char *line, t_data *data, t_parse **parse)
{
	parse_line(line, parse, &data->env);
	ft_expand(parse, data->env);
	check_quotes(parse);
	check_heredoc(parse, data->env);
	ft_lstcmd(&data, parse);
}