/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:34:57 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:33 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    LEXER_H
# define    LEXER_H

# include "token.h"
// # include "./get_next_line.h"
# include "../includes/execution.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>

typedef struct s_lexer
{
	char			**args;
	char			*cmd;
	char			*line;
	char			*contents;
	int				synt;
	unsigned long	i;
	char			c;
}	t_lexer;

t_lexer		*init_lexer(char	*contents);
void		lexer_advance(t_lexer	*lexer);
void		lexer_skip_whitespace(t_lexer	*lexer);
t_token		*lexer_get_next_token(t_lexer	*lexer);
char		*lexer_collect_string(t_lexer	*lexer);
t_token		*lexer_collect_id(t_lexer	*lexer);
t_token		*lexer_advance_with_token(t_lexer	*lexer, t_token	*token);
char		*lexer_get_current_char_as_string(t_lexer	*lexer);
t_token		*init_token(int type, char	*value, int z);
t_token		*ft_expand(t_token *toke, char **env);
char		*parser_get_current_char_as_string(char c);
char		*lexer_collect_string2(t_lexer	*lexer);
t_expand	*init_expand(t_token *toke);
void		token_skip_whitespace(t_expand	*lexer);
void		token_advance(t_expand	*lexer);
char		*ft_strjoi(char *s1, char *s2);
int			ft_strncmpp(char *s1, char *s2);
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
t_token		*lexer_get_next_token(t_lexer	*lexer);
char		*lexer_collect_string(t_lexer	*lexer);
t_token		*lexer_collect_id(t_lexer	*lexer);
char		*lexer_get_current_char_as_string(t_lexer	*lexer);
t_token		*init_token(int type, char	*value, int z);
t_lexer		*init_lexer(char *contents);
void		lexer_advance(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
void		lexer_advance_skip_ws(t_lexer *lexer);
char		*join1(t_lexer *lexer, char *value);
t_token		*lexer_collect_redirect2(t_lexer *lexer);
void		advance_one_skws(t_lexer *lexer);
t_token		*lexer_collect_redirect1(t_lexer *lexer);
char		*collect_doub_sing(t_lexer *lexer, int *z, char *value);
t_token		*lexer_collect_redirect3(t_lexer *lexer);
t_token		*lexer_collect_redirect4(t_lexer *lexer);
char		*lexer_collect_string2(t_lexer	*lexer);
t_token		*lexer_collect_pipe(t_token *took, t_lexer *lexer);
void		lexi_helper(t_token	*tmp, t_lexer *lex, t_token *toke);

#endif