/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:24:28 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/28 03:30:57 by mhabibi-         ###   ########.fr       */
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

char *expand_single(char *value, int i)
{
        int z = i;
    char *str = NULL;
    char *str2 = NULL;
    str = parser_get_current_char_as_string(value[z]);
            str2 = ft_strjoin(str2,str);
    z++;
    // printf("z = %d\n", z);
    while (value[z] != 39)
    {
        str = parser_get_current_char_as_string(value[z]);
            str2 = ft_strjoin(str2,str);
        // if (value[z] == 39)
        // {
        //     str = ft_substr(value, i+2,z - i - 2);
            // printf("habibi ------------%s -----------%d\n",  str2, z);
        //     break;
        // }
        z++;
    }
    str = parser_get_current_char_as_string(value[z]);
            str2 = ft_strjoin(str2,str);
    // printf("%s\n", str2);
    return (str2);
}

char* parser_get_current_char_as_string(char c)
{
    char* str = malloc(sizeof(char)*2);
    str[0] = c;
    str[1] = '\0';

    return str;
}
char *expand_nor(char *value, int i)
{
    int z = i;
    char *str = NULL;
    char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *str3 = calloc(1, sizeof(char));
    z+=1;
    while(isalnum(value[z]) != 0)
    {
        str = parser_get_current_char_as_string(value[z]);
        str3 = ft_strjoin(str3,str);
        z++;
    }
            // printf ("str3 : %s\n", str3);
    USER = getenv(str3);
    str2 = ft_strjoin(str2, USER);
    str3[0] = 0;

    // if (strlen(str2) == 1)
    // return (NULL);
    printf("salam%s\n", str2);
    return (str2); 
}
char *check_digits_and_$(char *value, int i)
{
    char *str = NULL;
    char *str3 = calloc(1, sizeof(char));
    // i -=3;
    // i--;
    while (value[i])
    {
        if (value[i] == '$')
        {
            str = parser_get_current_char_as_string(value[i]);
                str3 = ft_strjoin(str3,str);
                i++;
        }
        //  else
            while(isalnum(value[i]) != 0)
            {
                printf("value [i] -----= %c\n", value[i]);
                str = parser_get_current_char_as_string(value[i]);
                str3 = ft_strjoin(str3,str);
                i++;
                break;
            }
            if (value[i] == '"')
                break;
            // i++;
    }
    printf("str3 ======= %s\n", str3);
    return (str3);
}

char *expand_double(char *value, int i)
{
    int z = i;
    char *str = NULL;
    char *str2 = calloc(1, sizeof(char));
    char *USER = NULL;
    char *str3 = calloc(1, sizeof(char));
    // z++;
    // printf("z = %d\n", z);
    // if (i == strlen(value))
    //     printf ("hhskdjfkl\n");
    str = parser_get_current_char_as_string(value[z]);
    str2 = ft_strjoin(str2,str);
    z++;
    // if (value[z] >= '0' && value[z] <= '9')
    //     z++;
    while (value[z])
    {
            // if (value[z+1] == '$' || isdigit(value[z+1]) != 0)
            // {
            //     str2 = ft_strjoin(str2, check_digits_and_$(value, z));
            //     while(value[z] == '$' || isdigit(value[z]) != 0)
            //         z++;
            //     while(isalnum(value[z]) != 0)
            //         z++;
            // }
        if (value[z] == '$' && value[z+1] != '$' && isdigit(value[z+1]) != 0)
        {
            z+=1;
            while(isalnum(value[z]) != 0 )
            {
                str = parser_get_current_char_as_string(value[z]);
                str3 = ft_strjoin(str3,str);
                z++;
            }
            // printf ("str3 : %s\n", str3);
            USER = getenv(str3);
            str2 = ft_strjoin(str2, USER);
            str3[0] = 0;
        }
        else if (value[z] != '$')
        {
        if (value[z] == '"')
        {
            str = parser_get_current_char_as_string(value[z]);
            str2 = ft_strjoin(str2,str);
            z++;
            return (str2);
        }
            str = parser_get_current_char_as_string(value[z]);
            str2 = ft_strjoin(str2,str);
            // printf("%s z =%d \n", str2, z);
            z++;
        }
    }
    printf("str2 ===== %s\n", str2);
    if (strlen(str2) == 1)
        return (NULL);
    return (str2);
}

t_token *go_expand(t_token *toke)
{
    int i = 0;
    char *str = NULL;
    char *str3 = calloc(1, sizeof(char));
    while (toke->value[i])
    {
        if (toke->value[i] == '"')
        {
            
            printf("salam cv bikhir\n");
            str = expand_double(toke->value, i);
            // printf("hahowa dkhal str = %s\n", str);
            i++;
            str3 = ft_strjoin(str3, str);
            // printf("final = %s\n", str);
            while (toke->value[i] != '"')
                i++;
                // i++;
                printf("value = %c  str3 = %s\n", toke->value[i], str3);
        }
        // printf("heloooooooooooooo==-=-4908689576895689\n");
        if (toke->value[i] == 39)
        {
            printf("z = %d\n", i);
            str = expand_single(toke->value, i);
            i++;
            str3 = ft_strjoin(str3, str);
            printf("final = %s\n", str3);
            while (toke->value[i] != 39)
                i++;
            i++;
        }
        else if (toke->value[i] != '"' && toke->value[i] != 39)
        {
            if (toke->value[i] != '$' )
            {
                str = parser_get_current_char_as_string(toke->value[i]);
                str3 = ft_strjoin(str3,str);
                i++;
            }
            else
            {
                str3 = ft_strjoin(str3, expand_nor(toke->value, i));
                i++;
                while(isalnum(toke->value[i]) != 0)
                i++;
                printf("zzzzz = %d\n", i);
            }
        }
        if (toke->value[i] == '"' && toke->value[i+1] == '\0')
        {
            break;
        }
        printf("finaaaaaaaal ----- z = %d = \n%s\n", i, str3);
    }
    printf("finaaaaaaaal = \n%s\n", str3);
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
    t_token *tmp;
    tmp = toke;
    while (toke)
    {
        if (toke->type != 5 && toke->type != 3)
        {
            toke = check_toke(toke);
        }
        toke = toke->next;
    }
    return (toke);
}