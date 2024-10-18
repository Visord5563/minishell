/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:13:38 by saharchi          #+#    #+#             */
/*   Updated: 2024/10/18 02:58:49 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct g_signle
{
	int	sig_herdoc;
	int	sig_child;
	int	sig_int;
}	t_signle;

t_signle	g_sigl;

typedef struct s_flag
{
	int		flag;
	char	quote;
}	t_flag;

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
	int	fd_in;
	int	fd_out;
}	t_fd;

typedef struct s_cmd
{
	char			**args;
	t_fd			fd;
	int				flag;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	char			*cwd;
	int				flag;
}	t_env;

typedef struct s_parse
{
	char			*text;
	t_token			token;
	int				flag;
	int				fd_hdoc;
	struct s_parse	*next;
}	t_parse;

typedef struct s_data
{
	struct s_cmd	*cmd;
	struct s_env	*env;
	int				flag;
	int				temp;
	char			*path;
	int				flag_pipe;
	int				fd[2];
	int				cmd_index;
	int				*childpids;
	int				created_child;
	int				flag_exec;
}	t_data;

int		ft_echo(char **argv, t_env **env);
void	ft_exit(char **str, t_env **env);
int		ft_pwd(t_env *env);
void	ft_cd(char *arg, t_env **env);
void	real_env(t_env *a, t_data *data);
int		ft_export(char **cmd, t_env **env, t_data *data);
void	ft_unset(t_env **env, char **names);

char	*look_for_key(t_env *env, char *key);
void	free_env(t_env *env);
char	*get_home(t_env *env);
char	*get_oldpwd(t_env *env);
char	*set_env(t_env **env, char *name, char *value);
void	swap_tmp(t_env *tmp, t_env *tmp2);
void	print_export(t_env *env, t_data *data);
void	sort_env(t_env **env, t_data *data);
int		is_valid_key(char *var);
int		env_key_exists(t_env *env, char *key);
void	update_env(t_env **env, char *key, char *value);
void	add_or_update_env(t_env **env, char *key, char *value);
void	pipe_error(t_data *data, int *fd, int *flag);
void	wait_pid_fun(int cmd_index, int *childpids, t_data *data);
void	close_fd(int *fd);
void	exec_process(t_data *data, t_cmd *cmd_list, int flag);
void	failed_fork(t_data *data, int *fd);
void	help_cd(t_env **env, char *cwd);
void	help_with_error(t_env **env);
void	print_quit(int status);
void	initialize_data(t_data *data);
int		handle_status_update(int status, t_cmd *cmd_list, t_data *data);
void	one_bultin(t_data *data, t_cmd *cmd_list);
void	wait_this(t_data *data, int num_cmds);
int		check_syntax_export(t_env **env, char *str, int *flag);
// // -----------------------
void	help_ft_env(t_env **envs);
void	handle_redirection(t_cmd *cmd);
void	execute_this(t_data *data);
void	check_bultins(char **cmd, t_env **env, t_data *data);
int		if_bultins(char **cmd);
void	ft_error(char *str, int status);
void	print_command_not_found(char *command, t_data *data);
void	env_key_error(char **cmd, t_env **env, int i, char *msg);
void	add_env(t_env **envs, char *key, char *value);
char	**join_lst(t_env *env);
char	*get_path(char *cmd, t_env *env);

int		count_str(char *str, char *set, int flag);
char	**my_split(char *str, char *set, int flag);
t_parse	*ft_lstnew(char *content, t_token token);
void	ft_lstadd_back(t_parse **lst, t_parse *new);
t_parse	*ft_lstlast(t_parse *lst);
int		ft_lstsize(t_parse *lst);
void	ft_lstclear(t_parse *lst);
void	sighandel(int sig);
void	ft_expand(t_parse **parse, t_env *envs);
void	parse_line(char *line, t_parse **parse, t_env **env);
void	ft_env(t_env **envs, char **env, int flag);
void	ft_lstcmd(t_data **data, t_parse **parse);
void	check_quotes(t_parse **parse);
void	check_heredoc(t_parse **parse, t_env *env);
void	ft_lstclearcmd(t_cmd *cmd);
void	ft_free(char **str);
char	*delete_quotes(char *str);
char	*expand_str(char *str, t_env *envs, t_flag *flag);
char	*check_value(char *key, t_env *envs, int flag);
int		is_space(char *str);
t_cmd	*ft_lstnewcmd(char **content, t_fd fd, int flag);
void	ft_add_backcmd(t_cmd **cmd, t_cmd *new);
int		count_args(t_parse *parse);
void	print_error_quote(char quote);
void	print_error(char *text);
void	exit_status(t_env **env, char *status);
int		handle_expand(t_env *env, char *str, int token);
int		ha_re_in(char *file, t_env *env, int token);
int		ha_re_ou(char *file, t_env *env, int token);
void	parsing(char *line, t_data *data, t_parse **parse);
int		ch_fexp(char c, int i);
char	*return_value(char *str, int i, t_env *envs, t_flag *flag);
int		count_quotes(char *text);
int		ft_strlen2(char *str, char *set);
int		ft_strlen1(char *str, char *set);
int		get_fd(char *delimiter, int *fd1);
void	putstr_her(char *line, char *delimiter, t_env *env, int fd);
char	*add_quot(char *value, char quote);
int		count_forexp(char *str, int j);
char	is_quote(char *text);
int		is_space2(char c, char *set);
int		cont_str_nonq(char *str, char *set, int i, char *quote);
char	*expand_str_in_her(char *str, t_env *envs, t_flag *flag);

#endif