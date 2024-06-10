/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/06/10 19:46:30 by ehafiane         ###   ########.fr       */
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
    int i;
    int j;
    int index;

    index = 0;
    i = 0;
    while (line[i])
    {
        j = 0;
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
        if (line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            if (line[i] == '|')
                ft_lstadd_back(parse, ft_lstnew("|", PIPE, index++));
            else if (line[i] == '<' && line[i + 1] == '<')
            {
                ft_lstadd_back(parse, ft_lstnew("<<", HDOC, index++));
                i++;
            }
            else if (line[i] == '<' && line[i + 1] != '<')
            {
                ft_lstadd_back(parse, ft_lstnew("<", RIN, index++));
            }
            else if (line[i] == '>' && line[i + 1] == '>')
            {
                ft_lstadd_back(parse, ft_lstnew(">>", APP, index++));
                i++;
            }
            else
                ft_lstadd_back(parse, ft_lstnew(">", ROUT, index++));
            i++;
        }
        else if (line[i] == '"')
        {
            j = ++i; // Skip the initial double quote
			// Collect everything inside the double quotes
            while (line[i] && (line[i] != '"' || (line[i] == '"' && line[i-1] == '\\')))
                i++;
			// Add the double-quoted string to the parse list
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), DQ, index++));
            i++; // Skip the closing double quote
        }
        else if (line[i] == '\'')
        {
            j = ++i; // Skip the initial single quote
			// Collect everything inside the single quotes
            while (line[i] && (line[i] != '\'' || (line[i] == '\'' && line[i-1] == '\\')))
                i++;
			// Add the single-quoted string to the parse list
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), SQ, index++));
            i++; // Skip the closing single quote
        }
        else
        {
            j = i;
			// Collect a word until a delimiter or special character is found
            while (line[i] && !check(line[i]) && line[i] != '"' && line[i] != 39)
                i++;
			// Add the word to the parse list
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), WORD, index++));
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
        line = readline("🤯minishell :");
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

