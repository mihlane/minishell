/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by rarahhal          #+#    #+#             */
/*   Updated: 2023/01/19 23:49:05 by mhabibi-         ###   ########.fr       */
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
#include "readline/readline.h"
#include "readline/history.h"
# include "../execution/execut_libft/ex_libft.h"
# include "../parse/lexer.h"

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
	int	ginp;
	int	status;
	t_leak_lst	**leak_lst;
}	t_status;

t_status	*g_sts; 
// typedef struct s_exp
// {
// 	char			*var;
// 	char			*value;
// 	char			*str;
// 	int				i;
// 	struct s_exp	*next;
// }	t_exp;

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		**fd;
	pid_t	id[1024];
	int		check;
}	t_pipe;

char	*con_cattt(char *p, const char *s1, const char *s2);
char	*ft_strjoinn(char  *s1, char *s2);

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
// char	*expand_no_quote(char	*str, t_expand	*exp);
// char	*ret_expanded_quote(char	*str, t_expand	*exp, char *str2);


#endif