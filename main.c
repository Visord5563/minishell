/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/06/12 15:52:10 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void heredoc(const char *delimiter) {

    char *line;
    printf("Delimiter = '%s'\n", delimiter);

    while (1) {
        line = readline("> ");
        if (line == NULL) {
            break;
        }
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        free(line);
    }
}

int check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != 39 && c != '<' && c != '>' && c != '|')
		return (0);
	return (1);
}

int check_token(t_parse **parse, char *line, int *i, int *index)
{
        if (line[*i] == '|')
		{
			if ((*index) == 0)
			{
				printf("🤯Minishell: syntax error near unexpected token `|'\n"); 
				return (0);
			}
			if (line[*i + 1] == '|')
				(*i)++;
            ft_lstadd_back(parse, ft_lstnew("|", PIPE, (*index)++));
		}
        else if (line[*i] == '<' && line[*i + 1] == '<')
        {
            ft_lstadd_back(parse, ft_lstnew("<<", HDOC, (*index)++));
            (*i)++;
            heredoc("EOF");
        }
        else if (line[*i] == '<')
            ft_lstadd_back(parse, ft_lstnew("<", RIN, (*index)++));
        else if (line[*i] == '>' && line[*i + 1] == '>')
        {
            ft_lstadd_back(parse, ft_lstnew(">>", APP, (*index)++));
            (*i)++;
        }
        else
            ft_lstadd_back(parse, ft_lstnew(">", ROUT, (*index)++));
        (*i)++;
		return (1);
}

void check_syntax(t_parse **parse)
{
	t_parse *tmp = *parse;
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
		{
			printf("🤯Minishell: syntax error near unexpected token `|'\n");
			return ;
		}
		if (tmp->token == RIN && (!tmp->next || tmp->next->token == PIPE || tmp->next->token == ROUT || tmp->next->token == APP))
		{
			if (!tmp->next)
				printf("🤯Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("🤯Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
			return ;
		}
		if (tmp->token == ROUT && (!tmp->next || tmp->next->token == PIPE || tmp->next->token == ROUT || tmp->next->token == APP))
		{
			if (!tmp->next)
				printf("🤯Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("🤯Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
			return ;
		}
		if (tmp->token == APP && (!tmp->next || tmp->next->token == PIPE || tmp->next->token == ROUT || tmp->next->token == APP))
		{
			if (!tmp->next)
				printf("🤯Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("🤯Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
			return ;
		}
		if (tmp->token == HDOC && (!tmp->next || tmp->next->token == PIPE || tmp->next->token == ROUT || tmp->next->token == APP))
		{
			if (!tmp->next)
				printf("🤯Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("🤯Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
			return ;
		}
		tmp = tmp->next;
	}
}

void parse_line(char *line, t_parse **parse)
{
    int i = 0;
    int j = 0;
    int index = 0;
    char quote = '\0';
    int token = 0;

    while (line[i])
    {
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
        if (line[i] == '\0')
            break;

        if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
            if(!check_token(parse, line, &i, &index))
				return ;
		}
        else 
        {
            j = i;
            while (line[i])
            {
                if (quote == '\0' && (line[i] == '"' || line[i] == '\''))
				{
					if (line[i] == '"')
						token = 2;
					else
						token = 1;
                    quote = line[i];
				}
                else if (line[i] == quote)
                    quote = '\0';
                else if (quote == '\0' && check(line[i]))
                    break;
                i++;
            }
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), token, index++));
			token = 0;
        }
    }
	check_syntax(parse);
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
        line = readline("🤯\033[0;34mMinishell$ \033[0m");
        if (!line)
            break;
        if (strcmp(line, "env") == 0)
        {
            while (*env)
                printf("%s\n", *env++);
        }
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

