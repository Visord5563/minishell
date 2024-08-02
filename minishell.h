/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:38 by saharchi          #+#    #+#             */
/*   Updated: 2024/08/02 00:38:19 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <fcntl.h>


typedef struct s_flags {
    int exit_stat;
} t_flags;
t_flags g_flags;

typedef struct g_signle
{
	int sig_herdoc;
	int ma_in;
} t_signle;

t_signle g_sigl;

typedef enum s_token
{
	WORD,
	HDOC,
	RIN,
	APP,
	ROUT,
	PIPE,
}	t_token;

typedef struct s_fd
{
	int fd_in;
	int fd_out;
} t_fd;

typedef struct s_cmd
{
	char **args;
	t_fd fd;
	struct s_cmd *next;
} t_cmd;


typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_parse
{
	char *text; 
	t_token token;
	int flag;
	int fd_hdoc;
	struct s_parse *next;
} t_parse;

typedef struct s_data
{
	char *line;
	struct s_cmd *cmd;
	struct s_env *env;
} t_data;


// // -----------------------
int		ft_echo(char **argv);
void	ft_exit(char **str);
int		ft_pwd();
void	ft_cd(char *arg, t_env **env);
void	real_env(t_env *a, int i, char **cmd);
int		ft_export(char **cmd, t_env **env);
void ft_unset(t_env **env, const char *name);

// // -----------------------
void	handle_redirection(t_cmd *cmd);
void	execute_this(t_data *data);
void	check_bultins(char **cmd, t_env **env);
int		if_bultins(char **cmd);
void	ft_error(char *str, int status);
void print_command_not_found(const char *command);

// // -----------------------

// void	add_env(t_env **envs, char *key, char *value);

int		count_str(char *str, char *set);
char	**my_split(char *str, char *set);
t_parse	*ft_lstnew(char *content, t_token token);
void	ft_lstadd_back(t_parse **lst, t_parse *new);
t_parse	*ft_lstlast(t_parse *lst);
int		ft_lstsize(t_parse *lst);
void	ft_lstclear(t_parse *lst);
void	sighandel(int sig);
void	ft_expend(t_parse **parse, t_env *envs);
void	parse_line(char *line, t_parse **parse, t_env **env);
void	ft_env(t_env **envs, char **env);
void	ft_lstcmd(t_data **data, t_parse **parse);
void	check_quotes(t_parse **parse);
void	check_heredoc(t_parse **parse, t_env *env);
void	ft_lstclearcmd(t_cmd *cmd);
void	ft_free(char **str);
char	*delete_quotes(char *str);
char	*expend_str(char *str, t_env *envs);
char	*check_value(char *key, t_env *envs);
int		is_space(char *str);
t_cmd	*ft_lstnewcmd(char **content, t_fd fd);
void	ft_add_backcmd(t_cmd **cmd, t_cmd *new);
int		count_args(t_parse *parse);

#endif