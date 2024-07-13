/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/13 14:37:17 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != 39 && c != '<' && c != '>' && c != '|' )
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
		else if ((tmp->token == RIN || tmp->token == ROUT || tmp->token == APP || tmp->token == HDOC) && (!tmp->next || (tmp->next->token != WORD && tmp->next->token != SQ && tmp->next->token != DQ)))
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

void handle_quotes(char *line, int *i, char *quote, int *token)
{
    if (*quote == '\0' && (line[*i] == '"' || line[*i] == '\''))
    {
        *quote = line[*i];
        *token = (line[*i] == '"') ? 2 : 1;
    }
    else if (line[*i] == *quote)
    {
        *quote = '\0';
    }
}

void parse_line(char *line, t_parse **parse)
{
    int i = 0, j = 0, index = 0;
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
            if (!check_token(parse, line, &i, &index))
                return;
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
			if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
				i++;
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
	char quote = '\0';
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i++];
			if(quote != str[i])
				new[j++] = str[i++];
		}
		else if (str[i] == quote)
		{
			quote = '\0';
			i++;
		}
		else
			new[j++] = str[i++];
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

char *check_value(char *key, t_env *envs)
{
	t_env *tmp = envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}
int check_to(int token, int flag)
{
	if (flag == 0)
	{
		if (token == WORD || token == DQ)
			return (1);
		return (0);
	}
	else
	{
		if (token == WORD || token == DQ || token == SQ)
			return (1);
		return (0);
	}
}


char *expend_str(char *str, t_env *envs)
{
	int i;
	int j;
	char *new;
	char *strtmp;
	
	i = 0;
	strtmp = ft_strdup("");
	while(str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != '\0')
		{
			j = i + 1;
			new =	ft_substr(str, 0 , i);
			while (str[j] && ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z')))
				j++;
			strtmp = ft_strjoin(new, check_value(ft_substr(str, i + 1, j - i - 1), envs));
			i = ft_strlen(strtmp) - 1;
			strtmp = ft_strjoin(strtmp, ft_substr(str, j, ft_strlen(str) - j));
			free(new);
			str = strtmp;
		}
		i++;
	}
	return (str);
}

void ft_expend(t_parse **parse, t_env *envs)
{
	t_parse *tmp = *parse;

	while (tmp)
	{
		if (tmp->token == HDOC)
			tmp = tmp->next;
		else if (check_to(tmp->token, 0))
		{
			tmp->text = expend_str(tmp->text, envs);
		}
		tmp = tmp->next;
	}
}

void join_cmd(t_parse **parse)
{
	t_parse *tmp = *parse;
	t_parse *new;
	char *text;
	while (tmp)
	{
		if (check_to(tmp->token, 1))
		{
			text = ft_strdup(tmp->text);
			while (tmp->next && check_to(tmp->next->token, 1))
			{
				if(text[ft_strlen(text) - 1] == ' ')
					break;
				text = ft_strjoin(text, tmp->next->text);
				new = tmp->next;
				tmp->next = tmp->next->next;
				free(new);
			}
			tmp->text = text;
		}
		else if(tmp->token == ROUT || tmp->token == RIN || tmp->token == APP || tmp->token == HDOC)
				tmp = tmp->next;
		tmp = tmp->next;
	}
}

t_op	*ft_lstnewope(char *content, t_token token)
{
	t_op	*list;

	list = malloc(sizeof(t_op));
	if (!list)
		return (NULL);
	list->file = ft_strdup(content);
	list->token = token;
	list->next = NULL;
	return (list);
}

void ft_add_back_red(t_op **red, char *text, int token)
{
	t_op *new;
	t_op *tmp;
	new = malloc(sizeof(t_op));
	if (!new)
		return ;
	new->file = text;
	new->token = token;
	new->next = NULL;
	if (!*red)
	{
		*red = new;
		return ;
	}
	tmp = *red;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	printf("file: %s\n", new->file);
	printf("token: %d\n", new->token);
	printf("file: %s\n", (*red)->file);
	printf("token: %d\n", (*red)->token);
	exit(0);
}

// void ft_strcmd(t_cmd **cmd, t_parse *parse)
// {
// 	*cmd = malloc(sizeof(t_cmd));
// 	int i = 0;
// 	(*cmd)->args = NULL;
// 	(*cmd)->ops = NULL;
// 	(*cmd)->fd.fd_in = 0;
// 	(*cmd)->fd.fd_out = 1;
// 	(*cmd)->next = NULL;
// 	t_parse *tmp = parse;
// 	int j;
// 	while (tmp)
// 	{
// 		if (tmp->token == WORD || tmp->token == DQ || tmp->token == SQ)
// 		{
// 			i = 0;
// 			t_parse *tmp1 = tmp;
// 			while(tmp1)
// 			{
// 				if (tmp->token == PIPE)
// 					break;
// 				if (tmp1->token == WORD || tmp1->token == DQ || tmp1->token == SQ)
// 				{
					
// 					i++;
// 				}
// 				if (tmp1->token == ROUT || tmp1->token == RIN || tmp1->token == APP || tmp1->token == HDOC)
// 				{
// 					tmp1 = tmp1->next;
// 				}
// 				tmp1 = tmp1->next;
// 			}
// 			(*cmd)->args = malloc(sizeof(char *) * (i + 1));
// 			j = 0;
// 			while (j < i)
// 			{
// 				if(tmp->token == HDOC || tmp->token == ROUT || tmp->token == RIN || tmp->token == APP)
// 					tmp = tmp->next->next;
// 				(*cmd)->args[j] = ft_strdup(tmp->text);
// 				j++;
// 				tmp = tmp->next;
// 			}	
// 			(*cmd)->args[j] = NULL;
// 		}
// 		if (tmp && tmp->token == ROUT ||tmp->token == RIN || tmp->token == APP || tmp->token == HDOC)
// 		{
// 			ft_add_back_red(&(*cmd)->ops, parse->text, parse->token);
// 			tmp = tmp->next->next;
// 		}
// 		// else if (parse->token == PIPE)
// 		// {

// 		// 	printf("pipe: \n");
// 		// 	(*cmd)->next = malloc(sizeof(t_cmd));
// 		// 	(*cmd) = (*cmd)->next;
// 		// 	(*cmd)->args = NULL;
// 		// 	(*cmd)->red = NULL;
// 		// 	(*cmd)->fd_in = 0;
// 		// 	(*cmd)->fd_out = 1;
// 		// 	(*cmd)->next = NULL;
// 		// 	tmp = tmp->next;
// 		// }
// 		t_cmd *tmp2 = *cmd;
// 		int k = 0;
// 		while (tmp2->args[k])
// 		{
// 			printf("args: %s\n", tmp2->args[k]);
// 			k++;
// 		}
// 		// printf("file: %s\n", (*cmd)->ops->file);
// 		// printf("token: %d\n", tmp2->ops->token);
// 		// if(k > 0)
// 		// 	exit(0);
// 	}
// }

int heredoc(const char *delimiter, int token, t_env *env) {

    char *line;
    int fd;
    char *cd;

    cd = getcwd(NULL, 0);
    chdir("/tmp");
    fd = open("herdoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1) 
	{
        line = readline("> ");
        if (line == NULL)
            break;
        if (strcmp(line, delimiter) == 0) 
		{
            free(line);
            break;
        }
		if(token == WORD)
			line = expend_str(line, env);
        line = ft_strjoin(line, "\n");
        write(fd, line, ft_strlen(line));
        free(line);
    }
    chdir(cd);
    return fd;
}

int check_heredoc(t_parse **parse, t_env *env)
{
	t_parse *tmp = *parse;
	t_parse *new;
	int fd;

	fd = -1;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			fd = heredoc(tmp->next->text, tmp->next->token, env);
			new = tmp;
			tmp = tmp->next;
			free(new);
		}
		else
			tmp = tmp->next;
	}
	return (fd);
}

int main(int ac, char **av, char **env)
{
    char *line;
	t_data *data;
    t_parse *parse;
    (void)ac;
    (void)av;
	
	data = malloc(sizeof(t_data));
	data->cmd = NULL;
	data->env = NULL;
    while (1)
    {
        line = readline("\033[0;34mMinishell$ \033[0;30m");
        if (!line)
            break;
        parse_line(line, &parse);
		ft_env(&data->env, env);
		ft_expend(&parse, data->env);
		join_cmd(&parse);
		check_quotes(&parse);
		check_heredoc(&parse, data->env);
		t_parse *tmp = parse;
		while (tmp)
		{
			printf("text: %s token: %d\n", tmp->text, tmp->token);
			tmp = tmp->next;
		}
		// ft_strcmd(&data->cmd, parse);
        parse = NULL;
		
		if (line && *line)
        	add_history(line);
        if (strcmp(line, "env") == 0)
        {
			t_env *tmp = data->env;
            while (tmp)
			{
				printf("%s=%s\n", tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
		ft_lstclear(parse);
        free(line);
	}
	return (0);
}
