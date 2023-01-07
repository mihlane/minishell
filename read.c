/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:51:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/07 19:27:26 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include "token.h"



t_expand *rmv_quotes(t_expand *exp)
{
    // int k;
    // int i = 0;
    // int z = 0;
    // char *str2 = NULL;
    exp = exp->next;
    // while (exp)
    // {
    // i = 0;
    // z = 0;
    // while (exp->expanded[i])
    // {
    //     if (exp->expanded[i] == '"' || exp->expanded[i] == 39)
    //         z++;
    //     i++;
    // }
    // k = i - z;
    // str2 = malloc(sizeof(char) * ((i - z) + 1));
    // i = 0;
    // z = 0;
    // while (z < k)
    // {
    //     if (exp->expanded[i] != '"' && exp->expanded[i] != 39)
    //     {
    // printf("hola      %c\n", exp->expanded[i]);
    //         str2[z] = exp->expanded[i];
    //         z++;
    //         i++;
    //     }
    //     else
    //         i++;
    // }
    // str2[z] = 0;
    // exp->expanded = str2;
    // printf("toke after removing = %s\n", exp->expanded);
    // exp = exp->next;
    // }
    return (exp);
    
}




t_token *fill_stx(t_token *toke)
{
    t_token *tmp;
    tmp = toke;
    while (toke)
    {
        toke->type = 7;
        toke = toke->next;
    }
    toke = tmp;
    return (toke);
}
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
        lex->synt = -1;
        // return NULL;
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
        if (toke->type == 6 || toke->type == 7)
        {
            toke = tmp;
            toke = fill_stx(toke);
            printf("syntax error habibiiiiiiiiii\n");
            break;
        }
        // if (toke->value == NULL)
        // {
        //     printf("syntax error habibi\n");
        //     lex->synt = -1;
        //     return NULL;
        // }
        printf("token  = %s token type %d \n", toke->value, toke->type);
        // printf("token next = %d\n", toke->type);
        // printf("token next = %s\n", toke->value);
        i++;
        toke = toke->next;
    }
    toke = tmp;
    if (toke == NULL)
        return (NULL);
    return (toke);
    // printf("tokken = %s\n", toke->value);
    // printf("token next = %s\n", toke->next->value);
}
int main(int ac, char **av)
{
    char *str;
    t_token *toke;
    t_expand *exp;
    (void)av;
    while (ac)
{
    str = readline("\033[0;32m~ minishell\x1b[0m ");
    add_history(str);
    toke = lexi(str);
    if (toke->type != 7)
        exp = ft_expand(toke);
    exp = rmv_quotes(exp);
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
