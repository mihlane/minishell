/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:52:41 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/08 19:33:15 by mhabibi-         ###   ########.fr       */
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
    char *value; //$USER
    char c;
    struct token *next;
}t_token;

//rd2 = >>  append out | rd1 = > output | rd3 = <<  herdoc| rd4 = < input




typedef struct expand
{
    int i;
    char *value;
    int type;
    char c;
    char *expanded;
    int syntax;
    // struct expand *next;
}t_expand;

typedef struct s_command_node
{
    char                    **cmd;
    int                        infile;
    int                        outfile;
    struct s_command_node    *next;
}    t_command;

t_expand* init_expand(t_token *toke);
// void token_skip_whitespace(t_token* lexer);
// void token_advance(t_token* lexer);
// "$ USER"
// $5USER
// "$"
// $
//"' abort
#endif