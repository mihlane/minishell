/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:51:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/03 20:31:45 by mhabibi-         ###   ########.fr       */
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
    add_history(str);
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
// separe bhadok l3aybat
//"$USER"'$T'$HOME
//''""''""RRRRR$RF
//echo $
//echo "$4USER"
//$HOME...$USER'$HOME'"$USER"$l
//$nnnn$nnnn$kk..$USE you ignore everything before something that doesnt expanded



//expand 127;
//li ba9i ma khedamch 
// //"$PATH....$USER'$LLL',,,123$L$USER"
//echo $
