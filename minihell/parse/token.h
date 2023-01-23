/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:52:41 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 18:49:45 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_envp
{
	char	**env;
	int		status;
	char	*pwd;
	int		num_pipe;
}	t_envp;

typedef struct token
{
	int				i;
	int				syntax;
	int				type;
	char			*value;
	char			c;
	int				herd;
	struct token	*next;
	enum
	{
		TOKEN_ID,
		TOKEN_RD2,
		TOKEN_RD1,
		TOKEN_RD3,
		TOKEN_RD4,
		TOKEN_PIPE,
		TOKEN_EOF,
		TOKEN_ERR,
	}				e_tkn;
}	t_token;

typedef struct expand
{
	int		i;
	char	*value;
	int		type;
	char	c;
	char	*expanded;
	int		syntax;
}	t_expand;

typedef struct s_command_node
{
	char					**cmd;
	int						infile;
	int						outfile;
	int						err;
	struct s_command_node	*next;
}	t_command;

typedef struct s_exp
{
	char			*var;
	char			*value;
	char			*str;
	int				i;
	struct s_exp	*next;
}	t_exp;

char		*go_expandd(char *toke);
char		*expand_norre(char *exp, int i);
char		*str_expanded(char *str, char *exp, int *i, char *expanded);
char		*expand_doublee(char *exp, int i);
char		*join_no_doll_and_doll(char *str, char *toke,
				char *expanded, int *i);
char		*join_expand_s_d(char *expanded, char *toke, int *i);
char		*join_i_plus(char *str, char *expanded, int *i, char *exp);
char		*dollar_odamo_digit(char *expanded, char *str2, int *i, char *exp);
char		*expand_singlee(char *exp, int i);
char		*get_expanded_2doll_dig(char *expanded, char *exp, int *i);
char		*check_digitss_and_do(char *exp, int i);
char		*check_tokee(char *toke, int fd);
char		*ft_expandd(char *str, int fd);
void		execution(t_command *list, t_envp *my_env, int i);
int			pipes(int k, t_command *cmd, t_envp *my_env);
void		handle_signals(int sig);
void		fill_env(char *env[], t_envp *my_env);
t_expand	*init_expand(t_token *toke);
char		*ft_expandd(char *str, int fd);
char		*ft_strdup_p(const char *s1);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

#endif