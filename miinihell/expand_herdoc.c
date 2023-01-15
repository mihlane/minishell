/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 04:21:22 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/14 02:17:09 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"


// char	*ft_substr(char *str, size_t start, size_t len)
// {
// 	size_t	i;
// 	size_t	l;
// 	char	*sub;

// 	sub = malloc(sizeof(char) * len + 1);
// 	if (!sub)
// 		return (NULL);
// 	i = 0;
// 	l = 0;
// 	while (str[i])
// 	{
// 		if (i >= start && l < len)
// 		{
// 			sub[l] = str[i];
// 			l++;
// 		}
// 		i++;
// 	}
// 	sub[l] = '\0';
// 	return (sub);
// }

//"$HOME'$HOME'"'"$HOME"'
//""'"'$USER'"'
//"$HOME"'$HOME'"$HOME"

char *check_digitss_and_$(char *exp, int i)
{
    char *str = NULL;
    char *expanded = calloc(1, sizeof(char));
    // char *str3 = 
    // i -=3;
    // i--;
    while (exp[i] != '\0' && i < (int)strlen(exp))
    {
        if (exp[i] == '$')
        {
            str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
        }
         else
         {
            if (isdigit(exp[i]) != 0)
                i++;
            while(isalnum(exp[i]) != 0)
            {
                // printf("value [i] -----= %c\n", value[i]);
                str = parser_get_current_char_as_string(exp[i]);
               expanded = ft_strjoin(expanded,str);
                i++;
                // break;
            }
         
            if (exp[i] == '"')
            {
                str = parser_get_current_char_as_string(exp[i]);
               expanded = ft_strjoin(expanded,str);
               i++;
                // token_advance(exp);
                // break;
            }
         }
                // printf("hola %c\n", exp->c);
            // i++;
    }
    // printf("str3 ======= %s\n", str3);
    return (expanded);
}
char *expand_singlee(char *exp, int i)  
   {
// int z = i;
    // int z = i;
    char *str = NULL;
    char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *expanded = calloc(1, sizeof(char));;
    // char *str3 = calloc(1, sizeof(char));
    // z++;
    // printf("z = %d\n", z);
    // if (i == strlen(value))
    // if (value[z] >= '0' && value[z] <= '9')
    //     z++;
    str = parser_get_current_char_as_string(exp[i]);
    expanded = ft_strjoin(expanded,str);
    i++;
    while (exp[i] != '\0')
    {
        
            if (exp[i] == '$' && (exp[i+1] == '$' || isdigit(exp[i+1]) != 0))
            {
                // printf("hola\n");
                expanded = ft_strjoin(expanded, check_digitss_and_$(exp, i));
                while(exp[i] == '$' || isdigit(exp[i]) != 0)
                    i++;
                while(isalnum(exp[i]) != 0)
                    i++;
            }
            // printf ("str3 : %s\n", str3);
        if (exp[i] == '$' && exp[i+1] != '$' && isdigit(exp[i+1]) == 0)
        {
            // z+=1;
            // printf("hahowa dkhal\n");
            if (exp[i] == '$' && (isalnum(exp[i+1]) == 0))
            {
                str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
                // printf("expanded = %s\n", exp->expanded);
            }
            else{
            str2 = calloc(1, sizeof(char));
            i++;
            while(isalnum(exp[i]) != 0 )
            {
                // printf("hola\n");
                printf("%c\n", exp[i]);
                str = parser_get_current_char_as_string(exp[i]);
                // exp->expanded
                 str2= ft_strjoin(str2,str);
                i++;
            }
            // printf("user ========%s\n", str2);
            USER = getenv(str2);
            if (USER != NULL)
            {
                expanded = ft_strjoin(expanded, USER);
                // printf (" expaaaaaaand %s %d\n", exp->expanded, exp->i);
                // str3[0] = 0;
            }
            free (str2);
            }
        }
        else if (exp[i] != '$')
        {
            if (exp[i] == 39)
            {
                str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
                // printf("expanded = %s\n", exp->expanded);
                return (expanded);
            }
            // printf("charta = %c\n", exp->c);
            str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
            // printf("%s z =%d \n", str2, z);
            // z++;
        }
                    // printf("charta 1111111 = %c\n", exp->c);

    }
    // printf("str2 ===== %s\n", str2);
    if (strlen(str2) == 1)
        return (NULL);
    return (expanded);
}

// char* parser_get_current_char_as_string(char c)
// {
//     char* str = malloc(sizeof(char)*2);
//     str[0] = c;
//     str[1] = '\0';
//     return str;
// }
char *expand_norre(char *exp, int i)
{
    // int z = i;
    char *str = NULL;
    char *expanded = calloc(1, sizeof(char));
    // char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *str3 = calloc(1, sizeof(char));
    // z+=1;
    i++;
    while(isalnum(exp[i]) != 0)
    {
        str = parser_get_current_char_as_string(exp[i]);
        str3 = ft_strjoin(str3,str);
        i++;
    }
            // printf ("str3 : %s\n", str3);
    USER = getenv(str3);
    if (USER != NULL )
        expanded = ft_strjoin(expanded, USER);
    str3[0] = 0;

    // if (strlen(str2) == 1)
    // return (NULL);
    // printf("salam%s\n", expanded);
    return (expanded); 
}


char *expand_doublee(char *exp, int i)
{
    // int z = i;
    char *str = NULL;
    char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *expanded = calloc(1, sizeof(char));;
    // char *str3 = calloc(1, sizeof(char));
    // z++;
    // printf("z = %d\n", z);
    // if (i == strlen(value))
    // if (value[z] >= '0' && value[z] <= '9')
    //     z++;
    str = parser_get_current_char_as_string(exp[i]);
    expanded = ft_strjoin(expanded,str);
    i++;
    while (exp[i] != '\0')
    {
        
            if (exp[i] == '$' && (exp[i+1] == '$' || isdigit(exp[i+1]) != 0))
            {
                // printf("hola\n");
                expanded = ft_strjoin(expanded, check_digitss_and_$(exp, i));
                while(exp[i] == '$' || isdigit(exp[i]) != 0)
                    i++;
                while(isalnum(exp[i]) != 0)
                    i++;
            }
            // printf ("str3 : %s\n", str3);
        if (exp[i] == '$' && exp[i+1] != '$' && isdigit(exp[i+1]) == 0)
        {
            // z+=1;
            // printf("hahowa dkhal\n");
            if (exp[i] == '$' && (isalnum(exp[i+1]) == 0))
            {
                str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
                // printf("expanded = %s\n", exp->expanded);
            }
            else{
            str2 = calloc(1, sizeof(char));
            i++;
            while(isalnum(exp[i]) != 0 )
            {
                // printf("hola\n");
                printf("%c\n", exp[i]);
                str = parser_get_current_char_as_string(exp[i]);
                // exp->expanded
                 str2= ft_strjoin(str2,str);
                i++;
            }
            // printf("user ========%s\n", str2);
            USER = getenv(str2);
            if (USER != NULL)
            {
                expanded = ft_strjoin(expanded, USER);
                // printf (" expaaaaaaand %s %d\n", exp->expanded, exp->i);
                // str3[0] = 0;
            }
            free (str2);
            }
        }
        else if (exp[i] != '$')
        {
            if (exp[i] == '"')
            {
                str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
                // printf("expanded = %s\n", exp->expanded);
                return (expanded);
            }
            // printf("charta = %c\n", exp->c);
            str = parser_get_current_char_as_string(exp[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
            // printf("%s z =%d \n", str2, z);
            // z++;
        }
                    // printf("charta 1111111 = %c\n", exp->c);

    }
    // printf("str2 ===== %s\n", str2);
    if (strlen(str2) == 1)
        return (NULL);
    return (expanded);
}


char *go_expandd(char *toke)
{
    int i = 0;
    char *str = NULL;
    char *expanded = calloc(1, sizeof(char));
    // char *str3 = ;
    // printf("helooooooooo\n");
    // t_expand *exp = init_expand(toke);
    while (toke[i] != '\0' && i < (int)strlen(toke))
    {
        if (toke[i]== '"')
        {
            
            expanded = ft_strjoin(expanded, expand_doublee(toke, i));
            i++;
            while (toke[i] != '"')
                i++;
            i++;
            // exp->expanded = ft_strjoin(exp->expanded, str3);
            // printf("vaaaaaaaalue --------- = %s\n", exp->expanded);
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
        if (toke[i] == 39)
        {
            // printf("salam cv bikhir\n");
            // printf("z = %d\n", i);
             expanded = ft_strjoin(expanded, expand_singlee(toke, i));
                i++;
             while (toke[i] != 39)
                i++;
                i++;
            //  printf("EXpanded %s\n", exp->expanded);
            // i++;
            // str3 = ft_strjoin(str3, str);
            // while (toke->value[i] != 39)
            //     i++;
            // printf("final = %s %c\n", str3, toke->value[i]);
            // i++;
                // printf("value = %c  str3 = %s\n", toke->value[i], str3);
        }
        if ( toke[i] && toke[i] != '"' && toke[i] != 39)
        {
            if (toke[i] != '$' )
            {
                str = parser_get_current_char_as_string(toke[i]);
                expanded = ft_strjoin(expanded,str);
                i++;
            }
            else
            {
                expanded = ft_strjoin(expanded, expand_norre(toke, i));
                i++;
                while(isalnum(toke[i]) != 0)
                    i++;
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
    // printf("finaaaaaaaal = \n%s\n", expanded);
    toke = expanded;
    return (toke);
}
char  *check_tokee(char *toke)
{
    int i = 0;
    // t_expand *exp = NULL;
    while (toke[i])
    {
        if (toke[i] == '$')
        {
            toke = go_expandd(toke);
            break;
        }
        i++;
    }
    return (toke);
}
char    *ft_expandd(char *str)
{
    int i;
    // t_expand*exp2 = NULL;
    // t_expand *tmp2 = NULL;
    i = 0;
    // if (toke->type != 5 && toke->type != 3)
    // {
    //      exp2 = check_toke(toke);
    //      printf("hola\n");
    //      toke = toke->next;
    // }
    // tmp2 = exp2;
    // write(2, "a\n", 2);
    // printf("hahowa dkhal\n");
            str  = check_tokee(str);
            // printf("expaaaaaaaaaaaaand = %s\n", toke->value);
    // exp2 = tmp2;
    return (str);
}