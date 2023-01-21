/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:34:57 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/19 22:07:34 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    LEXER_H
# define    LEXER_H

# include "token.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>

typedef struct lexer
{
	char			**args;
	char			*cmd;
	char			*line;
	char			*contents;
	int				synt;
	unsigned long	i;
	char			c;
}t_lexer;

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

#endif