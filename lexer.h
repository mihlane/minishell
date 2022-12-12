/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:34:57 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/11 17:14:33 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef    LEXER_H
# define    LEXER_H

#include "token.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
typedef struct lexer
{
    char **args;
    char *cmd;
    char *line;
    char *contents;
    unsigned long i;
    char c;
}t_lexer;

t_lexer* init_lexer(char* contents);

void lexer_advance(t_lexer* lexer);

void lexer_skip_whitespace(t_lexer* lexer);

t_token* lexer_get_next_token(t_lexer* lexer);

t_token* lexer_collect_string(t_lexer* lexer);

t_token* lexer_collect_id(t_lexer* lexer);

t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token);

char* lexer_get_current_char_as_string(t_lexer* lexer);
t_token* init_token(int type, char* value);

# endif