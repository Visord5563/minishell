/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/06/11 04:15:33 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != 39 && c != '<' && c != '>' && c != '|')
		return (0);
	return (1);
}


void parse_line(char *line, t_parse **parse)
{
    int i = 0;
    int start;
    int index = 0;
    char quote = '\0';

    while (line[i])
    {
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
        if (line[i] == '\0')
            break;

        if (line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            if (line[i] == '|')
                ft_lstadd_back(parse, ft_lstnew("|", PIPE, index++));
            else if (line[i] == '<' && line[i + 1] == '<')
            {
                ft_lstadd_back(parse, ft_lstnew("<<", HDOC, index++));
                i++;
            }
            else if (line[i] == '<')
                ft_lstadd_back(parse, ft_lstnew("<", RIN, index++));
            else if (line[i] == '>' && line[i + 1] == '>')
            {
                ft_lstadd_back(parse, ft_lstnew(">>", APP, index++));
                i++;
            }
            else
                ft_lstadd_back(parse, ft_lstnew(">", ROUT, index++));
            i++;
        }
        else 
        {
            start = i;
            while (line[i])
            {
                if (quote == '\0' && (line[i] == '"' || line[i] == '\''))
                    quote = line[i];
                else if (line[i] == quote)
                    quote = '\0';
                else if (quote == '\0' && check(line[i]))
                    break;
                i++;
            }
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, start, i - start), WORD, index++));
        }
    }
}

int main(int ac, char **av, char **env)
{
    char *line;
    t_parse *parse;
    t_parse *print;
    (void)env;
    (void)ac;
    (void)av;

    while (1)
    {
        line = readline("🤯\033[0;34mMinishell:\033[0m");
        if (!line)
            break;
        parse_line(line, &parse);

        char *str[8] = {"WORD", "SQ", "DQ", "HDOC", "RIN", "APP", "ROUT", "PIPE"};
        print = parse;
        while (print)
        {
            printf("txt : %s %s\n", print->text, str[print->token]);
            print = print->next;
        }
        print = NULL;
        parse = NULL;
        add_history(line);
        free(line);
    }
}

