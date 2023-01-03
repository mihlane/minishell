/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:24:28 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/03 22:02:45 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"


char	*ft_substr(char *str, size_t start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*sub;

	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	l = 0;
	while (str[i])
	{
		if (i >= start && l < len)
		{
			sub[l] = str[i];
			l++;
		}
		i++;
	}
	sub[l] = '\0';
	return (sub);
}

//"$HOME'$HOME'"'"$HOME"'
//""'"'$USER'"'
//"$HOME"'$HOME'"$HOME"

t_expand *expand_single(t_expand *exp)
{
        // int z = i;
    char *str = NULL;
    // char *str2 = NULL;
    str = parser_get_current_char_as_string(exp->c);
           exp->expanded = ft_strjoin(exp->expanded,str);
    token_advance(exp);
    // printf("z = %d\n", z);
    while (exp->c != 39)
    {
        str = parser_get_current_char_as_string(exp->c);
            exp->expanded = ft_strjoin(exp->expanded,str);
            token_advance(exp);
        // if (value[z] == 39)
        // {
        //     str = ft_substr(value, i+2,z - i - 2);
            // printf("habibi ------------%s -----------%d\n",  str2, z);
        //     break;
        // }
        // z++;
    }
    str = parser_get_current_char_as_string(exp->c);
            exp->expanded = ft_strjoin(exp->expanded,str);
            token_advance(exp);
    // printf("%s\n", str2);
    return (exp);
}

char* parser_get_current_char_as_string(char c)
{
    char* str = malloc(sizeof(char)*2);
    str[0] = c;
    str[1] = '\0';

    return str;
}
t_expand *expand_nor(t_expand *exp)
{
    // int z = i;
    char *str = NULL;
    // char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *str3 = calloc(1, sizeof(char));
    // z+=1;
    token_advance(exp);
    while(isalnum(exp->c) != 0)
    {
        str = parser_get_current_char_as_string(exp->c);
        str3 = ft_strjoin(str3,str);
        token_advance(exp);
    }
            // printf ("str3 : %s\n", str3);
    USER = getenv(str3);
    if (USER != NULL )
        exp->expanded = ft_strjoin(exp->expanded, USER);
    str3[0] = 0;

    // if (strlen(str2) == 1)
    // return (NULL);
    // printf("salam%s\n", str2);
    return (exp); 
}
t_expand *check_digits_and_$(t_expand *exp)
{
    char *str = NULL;
    // char *str3 = calloc(1, sizeof(char));
    // i -=3;
    // i--;
    while (exp->c != '\0' && exp->i < (int)strlen(exp->value))
    {
        if (exp->c == '$')
        {
            str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
        }
         else
         {
            while(isalnum(exp->c) != 0)
            {
                // printf("value [i] -----= %c\n", value[i]);
                str = parser_get_current_char_as_string(exp->c);
               exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
                // break;
            }
         
            if (exp->c == '"')
            {
                str = parser_get_current_char_as_string(exp->c);
               exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
                // break;
            }
         }
                printf("hola %c\n", exp->c);
            // i++;
    }
    // printf("str3 ======= %s\n", str3);
    return (exp);
}

char *expand_double(t_expand *exp)
{
    // int z = i;
    char *str = NULL;
    char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    // char *str3 = calloc(1, sizeof(char));
    // z++;
    // printf("z = %d\n", z);
    // if (i == strlen(value))
    str = parser_get_current_char_as_string(exp->c);
    exp->expanded = ft_strjoin(exp->expanded,str);
    token_advance(exp);
    // if (value[z] >= '0' && value[z] <= '9')
    //     z++;
    while (exp->c != '\0')
    {
            printf("charta ---------= %c\n", exp->c);
            if (exp->c == '$' && (exp->value[exp->i+1] == '$' || isdigit(exp->value[exp->i+1]) != 0))
            {
                printf("hola\n");
                check_digits_and_$(exp);
                // while(value[z] == '$' || isdigit(exp->c) != 0)
                //     z++;
                // while(isalnum(value[z]) != 0)
                //     z++;
            }
            // printf ("str3 : %s\n", str3);
        if (exp->c == '$' && exp->value[exp->i+1] != '$' && isdigit(exp->value[exp->i+1]) == 0)
        {
            // z+=1;
            str2 = calloc(1, sizeof(char));
            token_advance(exp);
            while(isalnum(exp->c) != 0 )
            {
                printf("hola\n");
                printf("%c\n", exp->c);
                str = parser_get_current_char_as_string(exp->c);
                // exp->expanded
                 str2= ft_strjoin(str2,str);
                token_advance(exp);
            }
            printf("user ========%s\n", str2);
            USER = getenv(str2);
            if (USER != NULL)
            {
                exp->expanded = ft_strjoin(exp->expanded, USER);
                printf (" expaaaaaaand %s %d\n", exp->expanded, exp->i);
                // str3[0] = 0;
            }
            free (str2);
        }
        else if (exp->c != '$')
        {
            if (exp->c == '"')
            {
                str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
                printf("expanded = %s\n", exp->expanded);
                return (exp->expanded);
            }
            printf("charta = %c\n", exp->c);
            str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
            // printf("%s z =%d \n", str2, z);
            // z++;
        }
                    printf("charta 1111111 = %c\n", exp->c);

    }
    // printf("str2 ===== %s\n", str2);
    if (strlen(str2) == 1)
        return (NULL);
    return (exp->expanded);
}


t_token *go_expand(t_token *toke)
{
    // int i = 0;
    char *str = NULL;
    // char *str3 = calloc(1, sizeof(char));
    t_expand *exp = init_expand(toke);
    while (exp->c != '\0' && exp->i < (int)strlen(exp->value))
    {
        if (exp->c == '"')
        {
            
            expand_double(exp);
            // exp->expanded = ft_strjoin(exp->expanded, str3);
            printf("vaaaaaaaalue --------- = %s\n", exp->expanded);
            // printf("hahowa dkhal str = %s\n", str);

            

            //tal hna mzyan;


            
            // i++;
            // str3 = ft_strjoin(str3, str);
            // // printf("final = %s\n", str);
            // while (toke->value[i] != '"')
            //     i++;
            //     // i--;
            //     i++;
        }
        // printf("heloooooooooooooo==-=-4908689576895689\n");
        if (exp->c == 39)
        {
            printf("salam cv bikhir\n");
            // printf("z = %d\n", i);
             expand_single(exp);
             printf("EXpanded %s\n", exp->expanded);
            // i++;
            // str3 = ft_strjoin(str3, str);
            // while (toke->value[i] != 39)
            //     i++;
            // printf("final = %s %c\n", str3, toke->value[i]);
            // i++;
                // printf("value = %c  str3 = %s\n", toke->value[i], str3);
        }
        if ( exp->c && exp->c != '"' && exp->c != 39)
        {
            if (exp->c != '$' )
            {
                str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
            }
            else
            {
                expand_nor(exp);
                // i++;
                // while(isalnum(toke->value[i]) != 0)
                // i++;
                // printf("zzzzz = \n");
            }
        }
        // if (toke->value[i] == '\0')
        // {
        //     break;
        // }
        // if ( toke->value[i+1] == '\0' && toke->value[i] == '"')
        // {
        //     printf("salam\n");
        //     break;
        // }
        // i++;
        // printf("finaaaaaaaal ----- z = %d = \n%c\n", i, toke->value[i]);
    }
    printf("finaaaaaaaal = \n%s\n", exp->expanded);
    return (toke);
}
t_token *check_toke(t_token *toke)
{
    int i = 0;
    while (toke->value[i])
    {
        if (toke->value[i] == '$')
        {
            go_expand(toke);
            break;
        }
        i++;
    }
    return (toke);
}
t_token *ft_expand(t_token *toke)
{
    t_token *tmp = NULL;
    tmp = toke;
    while (toke)
    {
        if (toke->type != 5 && toke->type != 3)
        {
            toke = check_toke(toke);
        }
        toke = toke->next;
    }
    toke = tmp;
    return (toke);
}