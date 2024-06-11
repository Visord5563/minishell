/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/06/11 04:06:11 by saharchi         ###   ########.fr       */
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
    int f;
    int f2;
    int index;

    index = 0;
    i = 0;
	f = 0;
	f2 = 0;
    while (line[i])
    {
        j = 0;
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
		if (line[i] == '\0')
			break ;
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
        else 
        {
            j = i; 
            while (line[i])
			{
				if (check(line[i]) && f == 0)
					break ;
				if ((line[i] == '"' || line[i] == 39) && f == 0)
					f = 1;
				while (line[i])
				{
					printf("----%c %d\n", line[i] , f);
					if (line[i+1] == '"' || line[i+1] == 39)
					{
						i++;
						break ;
					}
					if (check(line[i]) && f == 1)
					{
						f2 = 1;
						break ;
					}
					i++;
				}
				if (f2 == 1)
					break ;
                i++;
			}
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

