/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/20 20:18:00 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../execution/execut_libft/ex_libft.h"
# include "../parse/lexer.h"
# include "../parse/token.h"

# define SIGHEREDOC 13
# define SIG_CHILD 37
# define SIGINT_ 1337

typedef struct s_leak_lst
{
	void				*content;
	struct s_leak_lst	*next;
}	t_leak_lst;

typedef struct s_status
{
	int			ginp;
	int			status;
	t_leak_lst	**leak_lst;
}	t_status;

t_status	*g_sts;

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		**fd;
	pid_t	id[1024];
	int		check;
}	t_pipe;

char		*con_cattt(char *p, const char *s1, const char *s2);
char		*ft_strjoinn(char	*s1, char *s2);
void		*alloc(size_t size);
void		*ft_calloc(size_t count, size_t size);
// builtins
void		ex_cd(char **sp, t_envp *my_env);
void		ex_env(char **sp, t_envp *my_env, int out);
void		ex_export(char **sp, t_envp *my_env, int out);
void		ex_unset(char **sp, t_envp *my_env);
void		ex_pwd(char **sp, t_envp *my_env, int out);
void		ex_echo(char **sp, t_envp *my_env, int out);
void		ex_exit(char **sp, t_envp *my_env, int k);
int			is_built(char *s);
void		__builtins(char **sp, t_envp *my_env, int out, int k);

//builtins_tools
int			ft_remove(t_envp *myenv, char *var);
int			ft_add2env(t_envp *myenv, char *var);
int			check_var(char *var, int a);
int			check_unset(char *var);
int			check_export(char *var);
int			__sort(char **s);
void		get_old(char **sp, t_envp *my_env);

//expand
int			is_str(char *s);
int			ft_isvalid(int c);
void		export_(char **arr, int out);
void		print_ar(char **arr, int out);
int			arr_s(char **s, char *str);
void		arr_cpy(t_envp *my_env, char *str);
void		arr_delete(t_envp *my_env, char **s, char *str);
char		*ft_cpy(char *s, int k);
size_t		arr_size(char *env[]);
void		fill_arr(char *env[], char *s[]);
t_exp		*ft_getvar(char *env[], t_exp *exp);
int			sk_ip(t_exp *tmp, char *s);
char		*ft_replace(char *s, char *old, char *new, int *k);
t_exp		*ft_getidx(t_exp *exp, char *s);

// Execute
int			pipes(int ac, t_command *cmd, t_envp *my_env);
void		multiple_p(t_pipe *p, int k, t_command *cmd, t_envp *my_env);
void		main_p(t_pipe *p, int k, t_command *cmd, t_envp *my_env);
void		main_wait(t_pipe *p, int k, t_envp *my_env, int ch);
void		f_close(t_pipe *p, int k);
t_command	*ex_comm(t_pipe *p, int k, t_command *cmd, t_envp *my_env);
char		*get_path(char *s, char *cmd);
void		one_cmd(t_envp *my_env, t_command *cmd);
void		frst_cmd(t_envp *my_env, int *fd, t_command *cmd);
void		next_cmd(t_envp *my_env, t_pipe *p, int i, t_command *cmd);
void		last_cmd(t_envp *my_env, int *fd, t_command *cmd);
void		ex_ecu(char *path, char *sp[], t_envp *my_env, int out);
void		ft_norm__(t_envp *my_env, t_pipe *p, int i, t_command *cmd);
void		er_ror(char *err, char *s);
int			sea_rch(char *s, int a);
char		*handle_env(char *env[]);
char		*skip_sl(char	*cmd);
char		*get_path(char *s, char *cmd);
void		ft_exit(char *sp[]);
void		free_arr(char **s);
t_expand	*check_digits_and_dollar(t_expand *exp, t_exp *expp);
t_expand	*expand_nor(t_expand *exp, t_exp *expp);
char		*expand_no_quote(char	*str, t_expand	*exp);
t_expand	*check_digits_and_dollar(t_expand *exp, t_exp *expp);
t_expand	*expand_last_moment(t_expand *exp, t_exp *expp);
t_expand	*check_digit_doll2(t_expand *exp, char *str);
t_expand	*check_digits_and_dollar(t_expand *exp, t_exp *expp);
char		*norm1(t_expand *exp, char	*user, t_exp *expp, char	*str);
char		*ret_expanded_quote(char	*str, t_expand	*exp);
char		*expand_no_quote(char	*str, t_expand	*exp);
char		*get_expanded_str2(char *str, char *str2, t_expand *exp);
t_exp		*ft_getidx(t_exp *exp, char *s);
char		*ft_getenv(t_exp *exp, char *s);
t_expand	*expand_single(t_expand *exp);
char		*parser_get_current_char_as_string(char c);
char		*join_itoa(t_expand *exp, int i);
t_expand	*amb_rdr(char	*str3, t_expand *exp);
t_expand	*expand_norr(t_expand *exp, t_exp *expp, char *str, char *str3);
char		*expand_double(t_expand *exp, t_exp *expp);
t_token		*go_expand(t_token *toke, t_exp *expp);
t_token		*go_expand(t_token *toke, t_exp *expp);
t_token		*check_toke(t_token *toke, t_exp *exp);
void		free_exp(t_exp **lst);
t_token		*ft_expand(t_token *toke, char **env);
t_token		*fill_stx(t_token *toke);
t_token		*lexi(char *str);
void		parse_norm(t_token **toke, t_command **cmds, t_envp **my_env);
void		disable_ctlc(void);
void		ft_putchar_fd(char c, int fd);
char		*ft_strjoin2(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
int			ft_open1(char *str);
int			ft_open2(char *str);
int			size(char *str, char *del);
char		*remove_new_line(char *line);
void		fun(int fd, char *delimeter, int i);
int			ft_open3(char *str, int i, int h);
int			ft_open4(char *str);
int			get_total_cmds(t_token *toke);
int			get_total_args(t_token *toke);
void		open_files(t_token **toke, t_command *nd, int h);
int			fill_struct(t_token **toke, t_command *nd, char **str, int z);
t_command	*create_node(t_token **toke);
void		ft_addback(t_command **node, t_command *new_node);
t_command	*ft_init(t_command **node, t_token **token);
t_command	*init_struct(t_token *toke);
char		*expand_double2(char *str, int i);
char		*expand_single2(char *str, int i);
int			get_index_double(char *str, int i);
int			get_index_single(char *str, int i);
char		*rmv_quotes_helper(char *value, char *str2);
t_token		*rmv_quotes(t_token *exp);
char		*dollar_ask(t_expand *exp);
void		arr_delete(t_envp *my_env, char **s, char *str);

#endif