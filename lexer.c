/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:18:27 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/07 12:25:22 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer* init_lexer(char* contents)
{
    t_lexer *lexer = malloc(sizeof(t_lexer));
    lexer->line = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];
    return lexer;
}

// void lexer_advance(t_lexer* lexer)
// {
    
// }

// void lexer_skip_whitespace(t_lexer* lexer)
// {
    
// }

// t_token* lexer_get_next_token(t_lexer* lexer)
// {
    
// }

// t_token* lexer_collect_string(t_lexer* lexer)
// {
    
// }

// t_token* lexer_collect_id(t_lexer* lexer)
// {
    
// }

// t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token)
// {
    
// }

// char* lexer_get_current_char_as_string(t_lexer* lexer)
// {
    
// }