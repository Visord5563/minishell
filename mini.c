/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/17 01:28:12 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != '<' && c != '>' && c != '|' )
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
		else if ((tmp->token == RIN || tmp->token == ROUT || tmp->token == APP || tmp->token == HDOC) && (!tmp->next || (tmp->next->token != WORD)))
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
                    quote = line[i];
                else if (line[i] == quote)
                    quote = '\0';
                else if (quote == '\0' && (check(line[i+1])))
				{
						i++;
						break;
				}
                i++;
            }
			if (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
				i++;
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), token, index++));
        }
    }
	if(quote != '\0')
	{
		printf("Minishell: syntax error near unexpected token `%c'\n", quote);
		ft_lstclear(*parse);
		*parse = NULL;
		return ;
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
	printf("str: \n");
	return (new);
}

void check_quotes(t_parse **parse)
{
	t_parse *tmp = *parse;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			printf("text: %s\n", tmp->text);
			tmp->text = delete_quotes(tmp->text);
			printf("text: %s\n", tmp->text);
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
		if (strcmp(tmp->key, key) == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return ("");
}

// int check_to(int token)
// {
// 		if (token == WORD)
// 			return (1);
// 		return (0);
// }


char *expend_str(char *str, t_env *envs)
{
	int i;
	int j;
	char *new;
	char *strtmp;
	char quote = '\0';
	
	i = 0;
	strtmp = ft_strdup("");
	while(str[i])
	{
		if(quote == '\0' && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if(quote != '\0' && (str[i] == '\'' || str[i] == '"'))
			quote = '\0';
		if ((str[i] == '$' && str[i + 1] != '$' && str[i+1] != ' ' && str[i + 1] != '\0' && quote != '\'' && str[i + 1] != '"' && str[i + 1] != '\'' && (ft_isdigit(str[i+1]) || ft_isalpha(str[i+1]) || str[i+1] == '_')) || (str[i] == '$' && quote == '\0' && str[i + 1] != '$' && str[i + 1] != '\0' && (ft_isdigit(str[i+1]) || ft_isalpha(str[i+1]) || str[i+1] == '_' || str[i + 1] == '"'|| str[i + 1] == '\'')))
		{
			j = i + 1;
			new =	ft_substr(str, 0 , i);
			while (str[j] && (ft_isdigit(str[j]) || ft_isalpha(str[j]) || str[j] == '_'))
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
		else if (tmp->token == WORD)
		{
			tmp->text = expend_str(tmp->text, envs);
		}
		tmp = tmp->next;
	}
}

char *delete_espace(char *str)
{
	int i = 0;
	int j = 0;
	char *new;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == '\0')
			break;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	free(str);
	return (new);
}

void join_cmd(t_parse **parse)
{
	t_parse *tmp = *parse;
	t_parse *new;
	char *text;
	while (tmp)
	{
		if (tmp->token == WORD)
		{
			text = ft_strdup(tmp->text);
			while (tmp->next)
			{
				if(text[ft_strlen(text) - 1] == ' ' || (text[ft_strlen(text) - 1] >= 9 && text[ft_strlen(text) - 1] <= 13))
					break;
				text = ft_strjoin(text, tmp->next->text);
				new = tmp->next;
				tmp->next = tmp->next->next;
				free(new);
			}
			tmp->text = text;
		}
		else if((tmp->next && (tmp->token == ROUT || tmp->token == RIN || tmp->token == APP || tmp->token == HDOC)))
				tmp = tmp->next;
		if(tmp->text[ft_strlen(tmp->text) - 1] == ' ' || (tmp->text[ft_strlen(tmp->text) - 1] >= 9 && tmp->text[ft_strlen(tmp->text) - 1] <= 13))
		{
			tmp->text = ft_strtrim(tmp->text, " \t\n\r\v\f");	
		}
		tmp = tmp->next;
	}
}




// void ft_strcmd(t_cmd **cmd, t_parse *parse)
// {
// }

int heredoc(char *delimiter, t_env *env) 
{

    char *line;
    int fd;
	char *s;
	
	s = ft_strjoin("/tmp/.", ft_itoa((int)delimiter));
    fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    unlink(s);
	free(s);
    fd = open(delimiter, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1) 
	{
        line = readline("> ");
        if (line == NULL)
            break;
		write(fd, delimiter, ft_strlen(line));
        if (strcmp(line, delete_quotes(delimiter)) == 0) 
		{
            free(line);
            break;
        }
		if(ft_strchr(delimiter, '\'') == 0  && ft_strchr(delimiter, '"') == 0)
		{		
			line = expend_str(line, env);
		}
        line = ft_strjoin(line, "\n");
        ft_putstr_fd(line, fd);
		printf("line: %s\n", line);
        free(line);
    }
    return fd;
}

int check_heredoc(t_parse **parse, t_env *env)
{
	t_parse *tmp;
	t_parse *new;
	int fd;

	fd = -1;
	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			fd = heredoc(tmp->next->text, env);
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
		check_heredoc(&parse, data->env);
		check_quotes(&parse);
		printf("line: \n");
		// ft_strcmd(&data->cmd, parse);
		// t_parse *tmp = parse;
		// while (tmp)
		// {
		// 	printf("text: [%s] token: %d\n", tmp->text, tmp->token);
		// 	tmp = tmp->next;
		// }
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

// void ft_lstcmd(t_data **data, t_parse *parse)
// {
// 	t_parse *tmpsize;
// 	char **args;
// 	int i;
// 	int j;
// 	int fd_in = 0;
// 	int fd_out = 1;
// 	while(parse)
// 	{
// 		i = 0;
// 		tmpsize = parse;
// 		while(tmpsize)
// 		{
// 			if(tmpsize->token == PIPE)
// 				break ;
// 			if(tmpsize->token == WORD)
// 				i++;
// 			tmpsize = tmpsize->next;
// 		}
// 		args = malloc(sizeof(char *) * (i + 1));
// 		j = 0;
// 		while(parse && parse->token != PIPE)
// 		{
// 			if (parse->token == WORD)
// 			{
// 				args[j] = ft_strdup(parse->text);
// 				j++;
// 			}
// 			else if(parse->token == HDOC || parse->token == RIN || parse->token == ROUT || parse->token == APP)
// 			{
// 				if(parse->token == HDOC)
// 				{
// 					fd_in = heredoc(parse->next->text, (*data)->env);
// 				}
// 				else if (parse->token == RIN)
// 				{
// 					fd_in = open(parse->next->text, O_RDONLY);
// 				}
// 				else if (parse->token == ROUT)
// 				{
// 					fd_out = open(parse->next->text, O_CREAT | O_RDWR | O_TRUNC | 0777);	
// 				}
// 				else if (parse->token == APP)
// 				{
// 					fd_out = open(parse->next->text, O_CREAT | O_RDWR | O_APPEND | 0777);
// 				}
// 			}
// 			parse = parse->next;
// 		}
// 		args[j] = NULL;
// 		parse = parse->next;
// 		ft_add_backcmd(&(*data)->cmd, ft_lstnewcmd(args, fd_in, fd_out));
// 		fd_in = 0;
// 		fd_out = 1;
// 		if(parse && parse->next)
// 			parse = parse->next;			
// 	}
// }

// void ft_lstcmd(t_data **data, t_parse *parse)
// {
//     t_cmd *tmp;
//     t_parse *tmpsize;
//     char **args;
//     int i;
//     int j;

//     while (parse)
//     {
//         tmp = malloc(sizeof(t_cmd));
//         if (!tmp)
//             return; // Handle malloc failure
//         tmp->fd = malloc(sizeof(t_fd));
//         if (!tmp->fd)
//         {
//             free(tmp);
//             return; // Handle malloc failure
//         }
//         tmp->fd->fd_in = 0;
//         tmp->fd->fd_out = 1;
//         tmp->next = NULL;
//         i = 0;
//         tmpsize = parse;
//         while (tmpsize && tmpsize->token != PIPE)
//         {
//             if (tmpsize->token == WORD)
//                 i++;
//             tmpsize = tmpsize->next;
//         }
//         args = malloc(sizeof(char *) * (i + 1));
//         if (!args)
//         {
//             free(tmp->fd);
//             free(tmp);
//             return; // Handle malloc failure
//         }
//         j = 0;
//         while (parse && parse->token != PIPE)
//         {
//             if (parse->token == WORD)
//             {
//                 args[j] = ft_strdup(parse->text);
//                 j++;
//             }
//             else if (parse->token == HDOC || parse->token == RIN || parse->token == ROUT || parse->token == APP)
//             {
//                 if (parse->token == HDOC)
//                 {
//                     tmp->fd->fd_in = heredoc(parse->next->text, (*data)->env);
//                 }
//                 else if (parse->token == RIN)
//                 {
//                     tmp->fd->fd_in = open(parse->next->text, O_RDONLY);
//                 }
//                 else if (parse->token == ROUT)
//                 {
//                     tmp->fd->fd_out = open(parse->next->text, O_CREAT | O_RDWR | O_TRUNC, 0777);
//                 }
//                 else if (parse->token == APP)
//                 {
//                     tmp->fd->fd_out = open(parse->next->text, O_CREAT | O_RDWR | O_APPEND, 0777);
//                 }
//             }
//             parse = parse->next;
//         }
//         args[j] = NULL; // Null-terminate the args array
//         tmp->args = args;
//         ft_add_backcmd(&(*data)->cmd, tmp);
//         if (parse && parse->token == PIPE)
//             parse = parse->next;
//     }
// }