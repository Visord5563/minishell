/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/04 10:14:26 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				printf("Minishell: syntax error near unexpected token `|'\n"); 
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
			printf("Minishell: syntax error near unexpected token `|'\n");
			return ;
		}
		else if ((tmp->token == RIN || tmp->token == ROUT || tmp->token == APP || tmp->token == HDOC) && (!tmp->next || tmp->next->token != WORD))
		{
			if (!tmp->next)
				printf("Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
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

t_env *ft_envnew(char *key, char *value)
{
	t_env *env;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

void add_env(t_env **envs, char *key, char *value)
{
	t_env *tmp;
	t_env *new;
	new = ft_envnew(key, value);
	if (!new)
		return ;
	if (!*envs)
	{
		*envs = new;
		return ;
	}
	tmp = *envs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void ft_env(t_env **envs, char **env)
{
	int i = 0;
	char *key = NULL;
	char *value = NULL;
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		add_env(envs, key, value);
		i++;
	}
}

char *delete_quotes(char *str)
{
	char *new;
	int i = 0;
	int j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

void check_quotes(t_parse **parse)
{
	t_parse *tmp = *parse;
	while (tmp)
	{
		if (tmp->token == SQ || tmp->token == DQ)
		{
			tmp->text = delete_quotes(tmp->text);
		}
		tmp = tmp->next;
	}
}

int	ft_strchrp(const char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int ft_val_key(t_env *tmp_env, char *key)
{
	t_env *new;
	new = tmp_env;
	while (new)
	{
		if (ft_strncmp(new->key, key, ft_strlen(key)) == 0)
				return (1);
		new = new->next;
	}
	return (0);
}

void ft_check_expend(char **str, t_env *tmp_env)
{
    int i = 0;
    int j = 0;
    char *new;
    char *key;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	if (!(*str)[i])
		return;
	j = i + 1;
    while ((*str)[j] && (((*str)[j] >= 'a' && (*str)[j] <= 'z') || ((*str)[j] >= 'A' && (*str)[j] <= 'Z')))
        j++;
    key = ft_substr(*str, i + 1, j - i - 1);
    while (tmp_env)
    {
        if (ft_strncmp(tmp_env->key, key, ft_strlen(key)) == 0)
        {
            new = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(tmp_env->value) + 1));
            if (!new)
            {
                free(key);
                return;
            }
            ft_strlcpy(new, *str, i+1);
            new[i] = '\0';
            new = ft_strjoin(new, tmp_env->value);
            new = ft_strjoin(new, *str + j);
            free(*str); 
            *str = new;
            break;
        }
		else if (ft_val_key(tmp_env, key) == 0)
		{
			new = malloc(sizeof(char) * (ft_strlen(*str) + 1));
			if (!new)
			{
				free(key);
				return;
			}
			ft_strlcpy(new, *str, i+1);
			new[i] = '\0';
			new = ft_strjoin(new, *str + j);
			free(*str);
			*str = new;
			break;
		}
        tmp_env = tmp_env->next;
    }
    free(key);
    if (ft_strchr(*str, '$'))
        ft_check_expend(str, tmp_env);
    else
        return;
}

void ft_expend(t_parse **parse, t_env *envs)
{
	t_parse *tmp = *parse;
	t_env *tmp_env;
	while (tmp)
	{
		if (tmp->token == WORD || tmp->token == SQ || tmp->token == DQ)
		{
			if (ft_strchr(tmp->text, '$'))
			{
				tmp_env = envs;
				ft_check_expend(&tmp->text, tmp_env);
				printf("%s\n", tmp->text);
			}
		}
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **env)
{
    char *line;
    t_parse *parse;
    // t_parse *print;
	t_env *envs = NULL;
    (void)ac;
    (void)av;

    while (1)
    {
        line = readline("🤯\033[0;34mMinishell$ \033[0m");
        if (!line)
            break;
        parse_line(line, &parse);
		ft_env(&envs, env);
		check_quotes(&parse);
		ft_expend(&parse, envs);
		ft_lstclear(parse);
        // print = NULL;
        parse = NULL;
		if (line && *line)
        	add_history(line);
        if (strcmp(line, "env") == 0)
        {
            while (*env)
                printf("%s\n", *env++);
        }
        add_history(line);
        free(line);
    }
	return (0);
}

