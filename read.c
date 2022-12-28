/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:51:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/28 03:34:03 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include "token.h"


t_token    *lexi(char *str)
{
    unsigned long i = 0;
    t_lexer *lex;
    t_token *tmp;
    t_token *toke;
    lex = init_lexer(str);
    lexer_skip_whitespace(lex);
    if (lex->line[lex->i] == '|')
    {
        printf("syntax error habibi\n");
        return NULL;
    }
    toke = lexer_get_next_token(lex);
    tmp = toke;
    while (toke && lex->i < strlen(lex->line))
    {
        toke->next = lexer_get_next_token(lex);
        toke = toke->next;
    }
    toke = tmp;
    // check_syntax_err(toke);
    i = 0;
    while (toke && i < strlen(lex->line))
    {
        printf("token  = %s token type %d \n", toke->value, toke->type);
        // printf("token next = %d\n", toke->type);
        // printf("token next = %s\n", toke->value);
        i++;
        toke = toke->next;
    }
    toke = tmp;
    return (toke);
    // printf("tokken = %s\n", toke->value);
    // printf("token next = %s\n", toke->next->value);
}
int main(int ac, char **av)
{
    char *str;
    t_token *toke;
    (void)av;
    while (ac)
{
    str = readline("\033[0;32m~ minishell\x1b[0m ");
    toke = lexi(str);
    ft_expand(toke);
    // printf("%s\n", str);
}
}

// "$l.g"
// $USER
//"$PATH....$USER'$LLL',,,123$L$USER"
//ls >'>'<<'a'>'file'a|pwd>'<<'
//echo $a_
//export a_=bk