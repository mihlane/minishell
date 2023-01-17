/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:24:28 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/17 11:39:21 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/execution.h"

t_exp	*ft_getidx(t_exp *exp, char *s)
{
	t_exp	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(s)) == 0
			&& ft_strlen(s) == ft_strlen(tmp->var))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

char *ft_getenv(t_exp *exp, char *s)
{
    t_exp *tmp;

    tmp = ft_getidx(exp, s);
    if (!tmp)
        return (NULL);
    return (tmp->value);
}
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

t_expand *check_digits_and_$(t_expand *exp);

t_expand *expand_single(t_expand *exp)
{
    char *str = NULL;
    str = parser_get_current_char_as_string(exp->c);
           exp->expanded = ft_strjoin(exp->expanded,str);
    token_advance(exp);
    while (exp->c != 39)
    {
        str = parser_get_current_char_as_string(exp->c);
            exp->expanded = ft_strjoin(exp->expanded,str);
            token_advance(exp);
    }
    str = parser_get_current_char_as_string(exp->c);
            exp->expanded = ft_strjoin(exp->expanded,str);
            token_advance(exp);
    return (exp);
}

char* parser_get_current_char_as_string(char c)
{
    char* str = malloc(sizeof(char)*2);
    str[0] = c;
    str[1] = '\0';
    return str;
}
t_expand *expand_nor(t_expand *exp, t_exp *expp)
{
    // int z = i;
    char *str = NULL;
    // char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *str3 = calloc(1, sizeof(char));
    // z+=1;
    if (exp->c == '$' && (exp->value[exp->i+1] == '$' || isdigit(exp->value[exp->i+1]) != 0))
        check_digits_and_$(exp);
    if (exp->c == '$' && exp->value[exp->i+1] == '?')
    {
	    exp->expanded = ft_strjoin (exp->expanded, ft_itoa(g_sts->status));
        printf("status = %d\n", g_sts->status);
        token_advance(exp);
        token_advance(exp);
    }
        if (exp->c == '$' && exp->value[exp->i+1] != '$' && isdigit(exp->value[exp->i+1]) == 0)
        {
            if (exp->c == '$' && (isalnum(exp->value[exp->i+1]) == 0))
            {
                str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
            }
            else
            {
            token_advance(exp);
            while(isalnum(exp->c) != 0 || exp->c == '_')
            {
                str = parser_get_current_char_as_string(exp->c);
                str3 = ft_strjoin(str3,str);
                token_advance(exp);
            }
    USER = ft_getenv(expp, str3);
    if (USER == NULL && exp->type > 0 && exp->type <=4)
    {
        printf("$%s: ambiguous redirect\n", str3);
        return (NULL);
    }
    if (USER != NULL )
        exp->expanded = ft_strjoin(exp->expanded, USER);
    str3[0] = 0;
            }
        }

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
            if (isdigit(exp->c) != 0)
                token_advance(exp);
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
                // printf("hola %c\n", exp->c);
            // i++;
    }
    // printf("str3 ======= %s\n", str3);
    return (exp);
}

char *expand_double(t_expand *exp, t_exp *expp)
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
        
            if (exp->c == '$' && (exp->value[exp->i+1] == '$' || isdigit(exp->value[exp->i+1]) != 0))
            {
                // printf("hola\n");
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
            // printf("hahowa dkhal\n");
            if (exp->c == '$' && (isalnum(exp->value[exp->i+1]) == 0))
            {
                str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
                // printf("expanded = %s\n", exp->expanded);
            }
            else{
            str2 = calloc(1, sizeof(char));
            token_advance(exp);
            while(isalnum(exp->c) != 0 || exp->c == '_')
            {
                // printf("hola\n");
                // printf("%c\n", exp->c);
                str = parser_get_current_char_as_string(exp->c);
                // exp->expanded
                 str2= ft_strjoin(str2,str);
                token_advance(exp);
            }
            // printf("user ========%s\n", str2);
            USER = ft_getenv(expp, str2);
            if (USER == NULL && exp->type > 0 && exp->type <=4)
            {
                printf("$%s: ambiguous redirect\n", str2);
                return (NULL);
            }
            if (USER != NULL)
            {
                exp->expanded = ft_strjoin(exp->expanded, USER);
                // printf (" expaaaaaaand %s %d\n", exp->expanded, exp->i);
                // str3[0] = 0;
            }
            free (str2);
            }
        }
        else if (exp->c != '$')
        {
            if (exp->c == '"')
            {
                str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
                // printf("expanded = %s\n", exp->expanded);
                return (exp->expanded);
            }
            // printf("charta = %c\n", exp->c);
            str = parser_get_current_char_as_string(exp->c);
                exp->expanded = ft_strjoin(exp->expanded,str);
                token_advance(exp);
            // printf("%s z =%d \n", str2, z);
            // z++;
        }
                    // printf("charta 1111111 = %c\n", exp->c);

    }
    // printf("str2 ===== %s\n", str2);
    if (strlen(str2) == 1)
        return (NULL);
    return (exp->expanded);
}


t_token *go_expand(t_token *toke, t_exp *expp)
{
    // int i = 0;
    char *str = NULL;
    // char *str3 = calloc(1, sizeof(char));
    t_expand *exp = init_expand(toke);
    while (exp->c != '\0' && exp->i < (int)strlen(exp->value))
    {
        if (exp->c == '"')
        {
            
            expand_double(exp, expp);
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
        if (exp->c == 39)
        {
            // printf("salam cv bikhir\n");
            // printf("z = %d\n", i);
             expand_single(exp);
            //  printf("EXpanded %s\n", exp->expanded);
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
                expand_nor(exp, expp);
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
    // printf("finaaaaaaaal = \n%s\n", exp->expanded);
    toke->value = exp->expanded;
    return (toke);
}
t_token *check_toke(t_token *toke, t_exp *exp)
{
    int i = 0;
    // t_expand *exp = NULL;
    while (toke->value[i])
    {
        if (toke->value[i] == '$')
        {
            toke = go_expand(toke, exp);
            break;
        }
        i++;
    }
    return (toke);
}
t_token *ft_expand(t_token *toke, char **env)
{
    t_token *tmp = NULL;
    t_exp *exp;

    // exp = malloc(sizeof(t_exp));
    exp = NULL;
    exp = ft_getvar(env, exp);
    // t_expand*exp2 = NULL;
    // t_expand *tmp2 = NULL;
    tmp = toke;
    // if (toke->type != 5 && toke->type != 3)
    // {
    //      exp2 = check_toke(toke);
    //      printf("hola\n");
    //      toke = toke->next;
    // }
    // tmp2 = exp2;
    while (toke)
    {
        if (toke->type != 5 && toke->type != 3)
        {
            toke = check_toke(toke, exp);
            // printf("expaaaaaaaaaaaaand = %s\n", toke->value);
        }
        // exp2 = exp2->next;
        toke = toke->next;
    }
    toke = tmp;
    while (toke)
    {
        // printf("tokekkkkkkk%s\n", toke->value);
        toke = toke->next;
    }
    toke = tmp;
    // exp2 = tmp2;
    return (toke);
}