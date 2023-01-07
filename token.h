/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:52:41 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/07 19:19:07 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef    TOKEN_H
# define    TOKEN_H

typedef struct token
{
    int i;
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
    } tkn;
    int type;
    char *value;
    char c;
    struct token *next;
}t_token;

typedef struct expand
{
    int i;
    char *value;
    int type;
    char c;
    char *expanded;
    int syntax;
    struct expand *next;
}t_expand;

t_expand* init_expand(t_token *toke);
// void token_skip_whitespace(t_token* lexer);
// void token_advance(t_token* lexer);
// "$ USER"
// $5USER
// "$"
// $
//"' abort
#endif