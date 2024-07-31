/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:31 by saharchi          #+#    #+#             */
/*   Updated: 2024/07/31 14:21:40 by ehafiane         ###   ########.fr       */
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
            ft_lstadd_back(parse, ft_lstnew(ft_strdup("|"), PIPE));
        else if (line[*i] == '<' && line[*i + 1] == '<')
        {
            ft_lstadd_back(parse, ft_lstnew(ft_strdup("<<"), HDOC));
            (*i)++;
        }
        else if (line[*i] == '<')
            ft_lstadd_back(parse, ft_lstnew(ft_strdup("<"), RIN));
        else if (line[*i] == '>' && line[*i + 1] == '>')
        {
            ft_lstadd_back(parse, ft_lstnew(ft_strdup(">>"), APP));
            (*i)++;
        }
        else
            ft_lstadd_back(parse, ft_lstnew(ft_strdup(">"), ROUT));
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
	free(str);
	return (new[j] = '\0', new);
}

void check_quotes(t_parse **parse)
{
	t_parse *tmp = *parse;
	while (tmp)
	{
		if(tmp->token == HDOC || tmp->flag == 1)
			tmp = tmp->next;
		else if (tmp->text)
		{
			if (ft_strchr(tmp->text, '\'') || ft_strchr(tmp->text, '"'))
				tmp->text = delete_quotes(tmp->text);
		}
		if(tmp)
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
			return (free(key), tmp->value);
		tmp = tmp->next;
	}
	return (free(key), "");
}

int is_space(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		i++;
	}
	return (0);

}
// char *check_value1(char *key, t_env *envs, int *flag)
// {
// 	t_env *tmp = envs;
// 	while (tmp)
// 	{
// 		if (strcmp(tmp->key, key) == 0)
// 		{
// 			if (is_space(tmp->value))
// 				*flag = 1;
// 			return (free(key), tmp->value);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (free(key), "");
// }

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
	free(str);
	return (strtmp);
}

int check_forexp(char c, int i)
{
	if (i == 0 && ((ft_isdigit(c) || ft_isalpha(c) || c == '_')))
			return (1);
	else if (i == 1 && (ft_isdigit(c) || ft_isalpha(c) || c == '_' || c == '"'|| c == '\''))
			return (1);
	return (0);
}


char *expend_str(char *str, t_env *envs)
{
	int i;
	char quote;
	
	i = 0;
	quote = '\0';
	while(str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
			i += 2;
		if(quote == '\0' && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if(quote == str[i] && (str[i] == '\'' || str[i] == '"'))
			quote = '\0';
		if (str[i] == '$' && ((quote != '\'' && check_forexp(str[i + 1], 0)) || (quote == '\0' && check_forexp(str[i + 1], 1))))
		{
			str = return_value(str, i, envs);
			i--;
		}
		if(ft_strcmp(str, "") == 0)
			return (str);
		i++;
	}
	return (str);
}

// char *ret_value(char *str, int i, t_env *envs, int *flag)
// {
// 	int j;
// 	char *new;
// 	char *strtmp;
	
// 	j = i + 1;
// 	new =	ft_substr(str, 0 , i);
// 	while (str[j] && (ft_isdigit(str[j]) || ft_isalpha(str[j]) || str[j] == '_'))
// 		j++;		
// 	strtmp = ft_strjoin(new, check_value1(ft_substr(str, i + 1, j - i - 1), envs, flag));
// 	i = ft_strlen(strtmp) - 1;
// 	strtmp = ft_strjoin(strtmp, ft_substr(str, j, ft_strlen(str) - j));
// 	free(new);
// 	free(str);
// 	return (strtmp);
// }

// char *ex_str(char *str, t_env *envs, int *flag)
// {
// 	int i;
// 	char quote;
	
// 	i = 0;
// 	quote = '\0';
// 	while(str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] == '$')
// 			i += 2;
// 		if(quote == '\0' && (str[i] == '\'' || str[i] == '"'))
// 			quote = str[i];
// 		else if(quote == str[i] && (str[i] == '\'' || str[i] == '"'))
// 			quote = '\0';
// 		if (str[i] == '$' && ((quote != '\'' && check_forexp(str[i + 1], 0)) || (quote == '\0' && check_forexp(str[i + 1], 1))))
// 		{
// 			str = ret_value(str, i, envs, flag);
// 			i--;
// 		}
// 		if(ft_strcmp(str, "") == 0)
// 			return (str);
// 		i++;
// 	}
// 	return (str);
// }

void ft_expend(t_parse **parse, t_env *envs)
{
	t_parse *tmp = *parse;

	while (tmp)
	{
		if (tmp->token == HDOC || tmp->token == RIN || tmp->token == APP || tmp->token == ROUT)
			tmp = tmp->next;
		else if (tmp->token == WORD)
		{
	
			tmp->text = expend_str(tmp->text, envs);
			if (is_space(tmp->text))
				tmp->flag = 1;
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

char *check_del(char *del)
{
	char *new;
	char quote;
	int i;
	int j;

	quote = '\0';
	i = 0;
	j = 0;
	if (ft_strchr(del, '$'))
	{	
		while(del[i])
		{
			j++;
			if(del[i] != '$')
				j = 0;
			if(quote == '\0' && (del[i] == '\'' || del[i] == '"'))
					quote = del[i];
				else if(quote == del[i] && (del[i] == '\'' || del[i] == '"'))
					quote = '\0';
			if (del[i] == '$' && quote == '\0' && (j % 2 != 0) && (del[i+1] == '\'' || del[i+1] == '"'))
			{
				new = ft_substr(del, 0, i);
				del = ft_strjoin(new, ft_substr(del, i+1, ft_strlen(del) - i+1));
				free(new);
				i--;
			}
			i++;
		}
	}
	if (ft_strchr(del, '"') || ft_strchr(del, '\''))
		del = delete_quotes(del);
	return(del);
}

int heredoc(char *delimiter, t_env *env) 
{
	char *line;
	char *del;
    int fd;
	char *s;
	
	char *runm = ft_itoa((int)delimiter);
	s = ft_strjoin(ft_strdup("/tmp/."), runm);
    fd = open(s,  O_CREAT | O_WRONLY | O_TRUNC, 0777);
    unlink(s);
	free(s);
	free(runm);
	g_sigl.sig_herdoc = 1;
    while (1) 
	{
	    line = readline("> ");
        if (line == NULL)
            break;
		if (ft_strchr(delimiter, '\'')  || ft_strchr(delimiter, '"')|| ft_strchr(delimiter, '$'))
			del = check_del(delimiter);
		else
			del = ft_strdup(delimiter);
        if (strcmp(line, del) == 0) 
		{
			free(del);
            free(line);
            break;
        }
		free(del);
		if(ft_strchr(delimiter, '\'') == 0  && ft_strchr(delimiter, '"') == 0)		
			line = expend_str(line, env);
		ft_putendl_fd(line, fd);
        free(line);
    }
	// g_sigl.sig_herdoc = 0;
    return (fd);
}

void check_heredoc(t_parse **parse, t_env *env)
{
	t_parse *tmp;
	int fd;
	
	fd = 0;
	tmp = *parse;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			if (fd != 0)
				close(fd);
			tmp->fd_hdoc = heredoc(tmp->next->text, env);
			if (g_sigl.sig_herdoc == 0 || tmp->fd_hdoc == -1)
			{
				dup2(1,0);
				ft_lstclear(*parse);
				*parse = NULL;	
				return;
			}
			fd = tmp->fd_hdoc;
			tmp = tmp->next;
		}
		if (tmp->token == PIPE)
			fd = 0;
		tmp = tmp->next;
	}
	g_sigl.sig_herdoc = 0;
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
		{
			if(parse->flag == 1)
				count += count_str(parse->text, " \t\n\v\f\r");
			else
            	count++;
		}
        parse = parse->next;
    }
    return count;
}

int handle_redirection_in(char *file, t_env *env) 
{
	int fd;
	if (ft_strchr(file, '$'))
		file = expend_str(file, env);
	if(is_space(file))
	{
		file = ft_strtrim(file, " \t\n\v\f\r");
		if (is_space(file) || ft_strcmp(file, "") == 0)
			return (-2);
	}
	fd = open(file, O_RDONLY, 0644);
	return (fd);
}

int handle_redirection_out(char *file, t_env *env, int token) 
{
	int fd;

	
	if (ft_strchr(file, '$'))
		file = expend_str(file, env);
	if(is_space(file))
	{
		file = ft_strtrim(file, " \t\n\v\f\r");
		if (is_space(file) || ft_strcmp(file, "") == 0)
			return (-2);
	}
	if (ft_strchr(file, '$') == 0)
		file = expend_str(file, env);
	if (token == ROUT)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0764);
	else
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0764);
	return (fd);
}

int handle_token(t_parse **parse, int *fd_in, int *fd_out, t_data **data) 
{
	
    if ((*parse)->token == HDOC || (*parse)->token == RIN)
	{
        if (*fd_in != 0)
            close(*fd_in);
		if((*parse)->token == HDOC)
        	*fd_in = (*parse)->fd_hdoc;
		else
        	*fd_in = handle_redirection_in((*parse)->next->text, (*data)->env);
    } 
	else if ((*parse)->token == ROUT || (*parse)->token == APP)
	{
        if (*fd_out != 1)
            close(*fd_out);
        *fd_out = handle_redirection_out((*parse)->next->text, (*data)->env, (*parse)->token);
    }  
    if (*fd_in == -1 || *fd_out == -1 || *fd_in == -2 || *fd_out == -2) 
	{
		if (*fd_in == -2 || *fd_out == -2)
		{
			ft_putstr_fd((*parse)->next->text, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
		}
		else
        	perror((*parse)->next->text);
        return(-1);
    }
    return(*parse = (*parse)->next, 0);
}

void ft_free(char **str)
{
	int i;

	i = 0;
	while(str[i])
		free(str[i++]);
	free(str);
}

int add_args(t_parse **parse, char ***args, t_data *data, t_fd *fd) 
{
    int j;
    int i;
	int k;
	char **str;

    i = count_args(*parse);
    *args = malloc(sizeof(char *) * (i + 1));
    if (!*args)
        return (-1);
    j = 0;
    fd->fd_in = 0;
    fd->fd_out = 1;
    while (*parse && (*parse)->token != PIPE) 
	{
        if ((*parse)->token == WORD) 
		{
            if (ft_strcmp((*parse)->text, ""))
			{
				if((*parse)->flag != 1)
                	(*args)[j++] = (*parse)->text;
				else
				{
					str = my_split((*parse)->text, " \t\n\v\f\r");
					k = 0;
					while (str[k])
						(*args)[j++] = delete_quotes(str[k++]);
					// ft_free(str);
				}
				
			}
        } 
		else if ((*parse)->token == HDOC || (*parse)->token == RIN || (*parse)->token == ROUT || (*parse)->token == APP)
            if (handle_token(parse, &fd->fd_in, &fd->fd_out, &data) == -1)
                return (-1);
        *parse = (*parse)->next;
    }
    (*args)[j] = NULL;
	return (0);
}

void ft_lstcmd(t_data **data, t_parse *parse) 
{
    t_fd *fd;
    char **args;

    while (parse) 
	{
        fd = malloc(sizeof(t_fd));
        if (!fd)
            return;
        if (add_args(&parse, &args, *data, fd) == -1 || !args)
		{
			ft_lstclearcmd((*data)->cmd);
			free(fd);
			free(args);
			(*data)->cmd = NULL;
			return;
		}
        ft_add_backcmd(&(*data)->cmd, ft_lstnewcmd(args, fd));
        if (parse)
			parse = parse->next;
    }
}

void sighandel(int sig)
{
    if (sig == SIGINT)
    {
		if(g_sigl.sig_herdoc == 1)
		{
			g_sigl.sig_herdoc = 0;
			close(0);
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
    }
}

int main(int ac, char **av, char **env)
{
    char *line;
	t_data *data;
    t_parse *parse;   //termios
    (void)ac;
    (void)av;
	
	data = malloc(sizeof(t_data));
	parse = NULL;
	data->cmd = NULL;
	data->env = NULL;
	ft_env(&data->env, env);
	rl_catch_signals = 0;
	signal(SIGINT, sighandel);
	signal(SIGQUIT, sighandel);
    while (1)
    {
        line = readline("\033[0;34mMinishell$ \033[0;37m");
        if (!line)
            break; 
        parse_line(line, &parse);
		ft_expend(&parse, data->env);
		check_quotes(&parse);
		check_heredoc(&parse, data->env);
		// t_parse *tmp1 = parse;
		// while (tmp1)
		// {
		// 	printf("text = %s\n", tmp1->text);
		// 	printf("token = %d\n", tmp1->token);
		// 	tmp1 = tmp1->next;
		// }
		ft_lstcmd(&data, parse);
		if (line && *line)
        	add_history(line);

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
		if (data->cmd )
			execute_this(data);
		ft_lstclearcmd(data->cmd);
		data->cmd = NULL;
		ft_lstclear(parse);
        parse = NULL;
        free(line);
	}
	return (0);
}
