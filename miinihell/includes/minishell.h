/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:22 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/11 16:23:11 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <unistd.h>
# include <string.h>

# include "libft.h"

# define SIGHEREDOC 13
# define SIG_CHILD 37
# define SIGINT_ 1337

typedef struct s_status
{
	int	ginp;
	int	status;
	int	check;
}	t_status;

t_status	*g_sts;

// ********************************************* token.h
typedef struct s_token
{
	char	*value;
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_IN,
		TOKEN_HERDOC,
		TOKEN_OU,
		TOKEN_APPAND,
		TOKEN_EOF,
	} e_type;
}	t_token;

t_token		*init_token(char *value, int type);

// ******************************************************** struct.h
typedef struct s_command_node
{
	char					**cmd;
	int						madir_walo;
	int						infile;
	int						outfile;
	int						splite[262144];
	struct s_command_node	*next;
}	t_command;

typedef struct s_envp
{
	char	**env;
	int		status;
	char	*pwd;
	int		num_pipe;
}	t_envp;

//************************************************* lexer.h
typedef struct s_lexer
{
	char			*src;
	size_t			src_size;
	char			c;
	unsigned int	i;
	t_token			*token;
	t_envp			*my_env;
	int				spliter;
	int				not_expand;
}	t_lexer;

t_lexer		*init_lexer(char *src);
void		lexer_advance(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
char		lexer_peek(t_lexer *lexer, int offset);
t_token		*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token		*lexer_advance_current(t_lexer *lexer, int type);
t_token		*lexer_next_token(t_lexer *lexer);
t_token		*help1_next_token(t_lexer *lexer);
t_token		*help2_next_token(t_lexer *lexer);
t_token		*lexer_collect_string(t_lexer *lexer);
char		*_free_value(char *value);

void		fill_env(char *env[], t_envp *my_env);

// ************************************************ parser.h
typedef struct s_parser
{
	char	**cmd;
	int		infile;
	int		outfile;
	int		no_assign;
	int		splite[262144];
}	t_parser;

t_command	*parser(t_lexer *lexer, t_token *token, t_command *list);
char		*get_string(t_envp *my_env, char *s, int count);

// *********************************************** tac.h
typedef struct s_tac
{
	t_lexer		*lexer;
	t_token		*token;
	t_command	*list;
	t_parser	*parser;
}	t_tac;

typedef struct s_heredoc
{
	int		i;
	char	*str;
	int		j;
	char	*del_to_name;
	int		k;
	int		fd;
	t_lexer	*lexer;
	t_token	*token;
}	t_heredoc;

int			tac_compile(char *src, t_envp *my_env);
int			check_syntax_error(char *src, int *i);
void		ft_free_(t_lexer *l, t_lexer *nl, t_token *t, t_token *nt);
int			unclosed_quotes(char *src, int **k);
void		_tac_free(t_lexer **lexer, t_token **token, char *src);

//heredoc
char		*here_doc(char *src, int stop, t_envp *my_env);
char		*_free_token(t_heredoc *here, char *src);
void		_tokenfree_(t_heredoc **here);
t_heredoc	*init__(char *src);
int			creat_heredoc(int fd, char *delemeter,
				t_envp *my_env, t_heredoc **here);
void		open_heredoc(int fd, char *delemeter, t_envp *my_env);

t_tac		*ft_rediriction(t_tac *tac);
t_tac		*next_command(t_tac **tac);
void		_free_(t_tac **tac, t_token **token, int k);
void		_free_t_v(t_token **token, char **value);

t_heredoc	*creat__file(t_heredoc *here, char *src, int stop);
t_heredoc	*get_delemeter(t_heredoc *here, char *src);

// function of linked list
t_command	*ft_lstnew(t_command **n1, char **s, int infile, int outfile);
t_command	*ft_lstlast(t_command *list);
void		free_string(char **s);
void		ft_addfront(t_command **list, t_command *new);

void		execution(t_command *list, t_envp *my_env);
int			pipes(int k, t_command *cmd, t_envp *my_env);

//   signals
void		handle_signals(int sig);

#endif
