/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:34:57 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/10 15:52:52 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef    LEXER_H
# define    LEXER_H

#include "token.h"
#include<fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "get_next_line.h"
typedef struct lexer
{
    char **args;
    char *cmd;
    char *line;
    char *contents;
    int synt;
    unsigned long i;
    char c;
}t_lexer;

t_lexer* init_lexer(char* contents);

void lexer_advance(t_lexer* lexer);

void lexer_skip_whitespace(t_lexer* lexer);

t_token* lexer_get_next_token(t_lexer* lexer);

char    * lexer_collect_string(t_lexer* lexer);

t_token* lexer_collect_id(t_lexer* lexer);

t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token);

char* lexer_get_current_char_as_string(t_lexer* lexer);
t_token* init_token(int type, char* value);
t_token *ft_expand(t_token *toke);
char	*ft_strjoin(char *s1, char *s2);
char* parser_get_current_char_as_string(char c);
char * lexer_collect_string2(t_lexer* lexer);
t_expand* init_expand(t_token *toke);
void token_skip_whitespace(t_expand* lexer);
void token_advance(t_expand* lexer);

# endif