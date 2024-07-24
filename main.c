/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/24 11:16:46 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check(char c)
{
	if (c != ' ' && !(c >= 9 && c <= 13) && c != '<' && c != '>' && c != '|' )
		return (0);
	return (1);
}

void check_token(t_parse **parse, char *line, int *i)
{
		if (line[*i] == '|')
            ft_lstadd_back(parse, ft_lstnew("|", PIPE));
        else if (line[*i] == '<' && line[*i + 1] == '<')
        {
            ft_lstadd_back(parse, ft_lstnew("<<", HDOC));
            (*i)++;
        }
        else if (line[*i] == '<')
            ft_lstadd_back(parse, ft_lstnew("<", RIN));
        else if (line[*i] == '>' && line[*i + 1] == '>')
        {
            ft_lstadd_back(parse, ft_lstnew(">>", APP));
            (*i)++;
        }
        else
            ft_lstadd_back(parse, ft_lstnew(">", ROUT));
        (*i)++;
}

int check_syntax(t_parse **parse)
{
	t_parse *tmp = *parse;
	
	if (tmp && tmp->token == PIPE)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return 1;
	}
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
		{
			printf("Minishell: syntax error near unexpected token `|'\n");
			return 1;
		}
		else if ((tmp->token == RIN || tmp->token == ROUT || tmp->token == APP || tmp->token == HDOC) && (!tmp->next || (tmp->next->token != WORD)))
		{
			if (!tmp->next)
				printf("Minishell: syntax error near unexpected token `newline'\n");
			else
				printf("Minishell: syntax error near unexpected token `%s'\n", tmp->next->text);
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

int str_len(char *line, int i, char *quote)
{
	int j = i;
	while (line[j])
	{
		if (*quote == '\0' && (line[j] == '"' || line[j] == '\''))
			*quote = line[j];
		else if (line[j] == *quote)
			*quote = '\0';
		else if (*quote == '\0' && (check(line[j])))
				break;
		j++;
	}
	return (j);
}

void parse_line(char *line, t_parse **parse)
{
    int i;
    int j;
    char quote;

	i = 0;
	quote = '\0';
    while (line[i])
    {
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
        if (line[i] == '|' || line[i] == '<' || line[i] == '>')
            check_token(parse, line, &i);
        else if (line[i] != '\0')
        {
			(1) && (j = i, i = str_len(line, i, &quote));
            ft_lstadd_back(parse, ft_lstnew(ft_substr(line, j, i - j), 0));
        }
	}
	if(quote != '\0' || check_syntax(parse) == 1)
	{
		if (quote != '\0')
			printf("Minishell: syntax error near unexpected token `%c'\n", quote);
		(1) && (ft_lstclear(*parse), *parse = NULL);
		return ;
	}
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
	int i;
	int j;
	char quote;
	
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
		{
			quote = str[i++];
			if(quote != str[i])
				new[j++] = str[i++];
		}
		else if (str[i] == quote)
			(1) && (quote = '\0', i++);
		else
			new[j++] = str[i++];
	}
	return (new[j] = '\0', new);
}

void check_quotes(t_parse **parse)
{
	t_parse *tmp = *parse;
	while (tmp)
	{
		if(tmp->token == HDOC)
			tmp = tmp->next;
		else if (tmp->text)
		{
			if (ft_strchr(tmp->text, '\'') || ft_strchr(tmp->text, '"'))
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
		if (strcmp(tmp->key, key) == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return ("");
}

char *return_value(char *str, int i, t_env *envs)
{
	int j;
	char *new;
	char *strtmp;
	
	j = i + 1;
	// strtmp = ft_strdup("");
	new =	ft_substr(str, 0 , i);
	while (str[j] && (ft_isdigit(str[j]) || ft_isalpha(str[j]) || str[j] == '_'))
		j++;		
	strtmp = ft_strjoin(new, check_value(ft_substr(str, i + 1, j - i - 1), envs));
	i = ft_strlen(strtmp) - 1;
	strtmp = ft_strjoin(strtmp, ft_substr(str, j, ft_strlen(str) - j));
	free(new);
	return (strtmp);
}

char *expend_str(char *str, t_env *envs)
{
	int i;
	char quote;
	
	i = 0;
	quote = '\0';
	while(str[i])
	{
		if(quote == '\0' && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if(quote == str[i] && (str[i] == '\'' || str[i] == '"'))
			quote = '\0';
		if (str[i] == '$' && ((quote != '\'' && (ft_isdigit(str[i+1]) || ft_isalpha(str[i+1]) || str[i+1] == '_')) || (quote == '\0' && (ft_isdigit(str[i+1]) || ft_isalpha(str[i+1]) || str[i+1] == '_' || str[i + 1] == '"'|| str[i + 1] == '\''))))
			str =return_value(str, i, envs);
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
	int i;
	int j;
	char *new;
	
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
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

t_cmd *ft_lstnewcmd(char **content, t_fd *fd)
{
    t_cmd *list;

    list = malloc(sizeof(t_cmd));
    if (!list)
        return (free(fd), NULL);
    list->args = content;
    list->fd = fd;
    list->next = NULL;
    return (list);
}

t_cmd *ft_lstlastcmd(t_cmd *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}


void ft_add_backcmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*node;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	node = *cmd;
	node = ft_lstlastcmd(*cmd);
	node->next = new;	
}

int heredoc(char *delimiter, t_env *env) 
{
	char *line;
    int fd;
	char *s;
	
	s = ft_strjoin("/tmp/.", ft_itoa((int)delimiter));
    fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    unlink(s);
	free(s);
    while (1) 
	{
        line = readline("> ");
        if (line == NULL)
            break;
        if (strcmp(line, delete_quotes(delimiter)) == 0) 
		{
            free(line);
            break;
        }
		if(ft_strchr(delimiter, '\'') == 0  && ft_strchr(delimiter, '"') == 0)		
			line = expend_str(line, env);
		ft_putendl_fd(line, fd);
        free(line);
    }
    return fd;
}

void ft_lstclearcmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->args);
		free(cmd->fd);
		free(cmd);
		cmd = tmp;
	}
}


int count_args(t_parse *parse) 
{
    int count = 0;
    while (parse && parse->token != PIPE) {
        if (parse->token == WORD)
            count++;
        parse = parse->next;
    }
    return count;
}

int handle_token(t_parse **parse, int *fd_in, int *fd_out, t_data *data) 
{
    if ((*parse)->token == HDOC || (*parse)->token == RIN)
	{
        if (*fd_in != 0)
            close(*fd_in);
		if((*parse)->token == HDOC)
        	*fd_in = heredoc((*parse)->next->text, data->env);
		else
        	*fd_in = open((*parse)->next->text, O_RDONLY, 0644);
    } 
	else if ((*parse)->token == ROUT || (*parse)->token == APP)
	{
        if (*fd_out != 1)
            close(*fd_out);
		if ((*parse)->token == ROUT)
        	*fd_out = open((*parse)->next->text, O_CREAT | O_RDWR | O_TRUNC, 0764);
		else
        	*fd_out = open((*parse)->next->text, O_CREAT | O_RDWR | O_APPEND, 0764);
    }  
    if (*fd_in == -1 || *fd_out == -1) 
	{
        perror((*parse)->next->text);
		ft_lstclearcmd(data->cmd);
        return(data->cmd = NULL, -1);
    }
    return(*parse = (*parse)->next, 0);
}

void add_args(t_parse **parse, char ***args, t_data *data, t_fd *fd) 
{
    int j;
    int i;

    i = count_args(*parse);
    *args = malloc(sizeof(char *) * (i + 1));
    if (!*args)
        return;
    j = 0;
    fd->fd_in = 0;
    fd->fd_out = 1;
    while (*parse && (*parse)->token != PIPE) 
	{
        if ((*parse)->token == WORD) 
		{
            if (ft_strcmp((*parse)->text, ""))
                (*args)[j++] = ft_strdup((*parse)->text);
        } 
		else if ((*parse)->token == HDOC || (*parse)->token == RIN || (*parse)->token == ROUT || (*parse)->token == APP)
            if (handle_token(parse, &fd->fd_in, &fd->fd_out, data) == -1)
                return;
        *parse = (*parse)->next;
    }
    (*args)[j] = NULL;
}

void ft_lstcmd(t_data **data, t_parse *parse) 
{
    t_fd *fd;
    char **args;

    while (parse) {
        fd = malloc(sizeof(t_fd));
        if (!fd)
            return;
        add_args(&parse, &args, *data, fd);
        if (!args) {
            free(fd);
            return;
        }
        ft_add_backcmd(&(*data)->cmd, ft_lstnewcmd(args, fd));
        if (parse)
			parse = parse->next;
    }
}

int main(int ac, char **av, char **env)
{
	// printf("check shell level\n");
    char *line;
	t_data *data;
    t_parse *parse;
    (void)ac;
    (void)av;
	
	data = malloc(sizeof(t_data));
	parse = NULL;
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
		check_quotes(&parse);
		// exit(0);
		ft_lstcmd(&data, parse);
		// t_parse *tmp1 = parse;
		// while (tmp1)
		// {
		// 	printf("text = %s\n", tmp1->text);
		// 	printf("token = %d\n", tmp1->token);
		// 	tmp1 = tmp1->next;
		// }
		// t_cmd *tmp = data->cmd;
		// int i = 0;
		// while (tmp)
		// {
		// 	printf("----------------cmd--------------------\n");
		// 	printf("fd_in = %d\n", tmp->fd->fd_in);
		// 	printf("fd_out = %d\n", tmp->fd->fd_out);
		// 	while (tmp->args[i])
		// 	{
		// 		printf("args[%d] = %s\n", i, tmp->args[i]);
		// 		i++;
		// 	}
		// 	i = 0;
		// 	tmp = tmp->next;
		// }
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
		if((data->cmd) && if_bultins(data->cmd->args))
			check_bultins(data->cmd->args, data->env);
		else if (data->cmd)
			execute_this(data);
		ft_lstclearcmd(data->cmd);
		data->cmd = NULL;
		ft_lstclear(parse);
        parse = NULL;
        free(line);
	}
	return (0);
}