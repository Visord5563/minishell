/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/06/11 03:10:43 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != 39 && c != '<' && c != '>' && c != '|')
		return (0);
	return (1);
}

void check_token(t_parse **parse, char *line, int i, int j)
{
    if (line[i] == '|')
        ft_lstadd_back(parse, ft_lstnew("|", PIPE, j));
    else if (line[i] == '<' && line[i + 1] == '<')
    {
        ft_lstadd_back(parse, ft_lstnew("<<", HDOC, j));
        i++;
    }
    else if (line[i] == '<' && line[i + 1] != '<')
    {
        ft_lstadd_back(parse, ft_lstnew("<", RIN, j));
    }
    else if (line[i] == '>' && line[i + 1] == '>')
    {
        ft_lstadd_back(parse, ft_lstnew(">>", APP, j));
        i++;
    }
    else
        ft_lstadd_back(parse, ft_lstnew(">", ROUT, j));
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
        if (line[i] == '\0')
            break;
        if (line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            check_token(parse, line, i, index++);
            i++;
        }
        else if (line[i] == '"')
        {
            j = i++; // Include the initial double quote
            while (line[i] && (line[i] != '"' || (line[i] == '"' && line[i-1] == '\\')))
                i++;
            if (line[i] == '"') // Include the closing double quote
                i++;
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), DQ, index++));
        }
        else if (line[i] == '\'')
        {
            j = i++; // Include the initial single quote
            while (line[i] && (line[i] != '\'' || (line[i] == '\'' && line[i-1] == '\\')))
                i++;
            if (line[i] == '\'') // Include the closing single quote
                i++;
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), SQ, index++));
        }
        else if (line[i] != ' ')
        {
            j = i;
            while (line[i] && !check(line[i]) && line[i] != '"' && line[i] != '\'')
                i++;
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

