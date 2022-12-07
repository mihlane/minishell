/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 01:34:57 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/07 12:23:24 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef    LEXER_H
# define    LEXER_H

#include "token.h"
#include <stdlib.h>

typedef struct lexer
{
    char **args;
    char *cmd;
    char *line;
    int i;
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

# endif