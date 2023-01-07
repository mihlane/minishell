/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:18:27 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/07 00:33:25 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

t_lexer* init_lexer(char* contents)
{
    t_lexer *lexer = malloc(sizeof(t_lexer));

    lexer->line = contents;
    lexer->i = 0;
    lexer->c = lexer->line[lexer->i];
    lexer->synt = 1;
    return lexer;
}

void lexer_advance(t_lexer* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        lexer->i += 1;
        lexer->c = lexer->line[lexer->i];
    }
}

void lexer_skip_whitespace(t_lexer* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10)
    {
        lexer_advance(lexer);
    }
}
t_token *lexer_collect_redirect2(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    lexer_advance(lexer);
    lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    // printf("helo\n");
    // printf ("in in\n");
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("synatx error\n");
            lexer->synt = -1;
            // return NULL;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
           if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
            // return (took);
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
            // return (took);
        }
        if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        // printf ("yeah\n");
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    // lexer_advance(lexer);
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        // return NULL;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value);
        
    return init_token(TOKEN_RD2, value);
}
t_token *lexer_collect_redirect1(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    lexer_advance(lexer);
    // lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    // printf("helo\n");
    if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("synatx error\n");
            return NULL;
        }
    // printf ("in in\n");
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
         if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
            // return (took);
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
            // return (took);
        }
        if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    // lexer_advance(lexer);
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        // return NULL;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value);
    return init_token(TOKEN_RD1, value);
}
t_token *lexer_collect_redirect3(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    lexer_advance(lexer);
    lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("syntax error\n");
            lexer->synt = -1;
            // return NULL;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line)  && lexer->c != ' ' && lexer->c != 10)
    {
        // printf ("yeah\n");
           if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
            // return (took);
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
            // return (took);
        }
         if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    // lexer_advance(lexer);
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        // return NULL;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value);
    return init_token(TOKEN_RD3, value);
}
t_token *lexer_collect_redirect4(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    // lexer_advance(lexer);
    lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("synatx error\n");
            lexer->synt = -1;
            // return NULL;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
        // printf ("yeah\n");
           if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
            // return (took);
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
            // return (took);
        }
        if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    // lexer_advance(lexer);
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        // return NULL;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value);
    printf("hahowa ja\n");
    return init_token(TOKEN_RD4, value);
}

char * lexer_collect_string2(t_lexer* lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    // lexer_advance(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        // printf ("yeah %c\n", lexer->c);
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
        if (lexer->c == 39)
        // && lexer->line[lexer->i+1] == ' ')
        {
            s = lexer_get_current_char_as_string(lexer);
            value = ft_strjoin(value, s);
            break;
        }
        // if (lexer->c == 39 )
        //    {
        //     s = lexer_get_current_char_as_string(lexer);
        //     value = ft_strjoin(value, s);
        //     break;
        // } 
        // if (lexer->line[lexer->i+1] == '"'')
        //     break;
    }
    lexer_advance(lexer);
     if (value[1] == '\0' || value[strlen(value) - 1] != 39)
    {
        printf("syntax error\n");
        lexer->synt = -1;
        // return NULL;
    }
    // printf("value =  %s\n", value);
    return value;
}

t_token* lexer_get_next_token(t_lexer* lexer)
{
    t_token *took = NULL;            
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);


        // else    if (lexer->c == '|')
        if (lexer->c == '>' && lexer->line[lexer->i+1] == '>')
        {
                printf("hola rd 2 %c %c \n", lexer->c,lexer->line[lexer->i+1] );
            took = lexer_collect_redirect2(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
        if (lexer->c == '>' && lexer->line[lexer->i+1] != '>')
        {
                printf("hola rd 1 %c %c \n", lexer->c,lexer->line[lexer->i+1] );
            took = lexer_collect_redirect1(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
           if (lexer->c == '<' && lexer->line[lexer->i+1] == '<')
        {
            printf("hola rd 3 %c %c \n", lexer->c,lexer->line[lexer->i+1] );
            took = lexer_collect_redirect3(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
        if (lexer->c == '<' && lexer->line[lexer->i+1] != '<')
        {
            printf("hola rd 4 %c %c \n", lexer->c,lexer->line[lexer->i+1] );
            took = lexer_collect_redirect4(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
         if (lexer->c == '|')
         {
            lexer_advance(lexer);
            lexer_skip_whitespace(lexer);
            if (lexer->line[lexer->i] == '\0')
            {
                printf("syntax error\n");
                lexer->synt = -1;
                // return NULL;
            }
            if (lexer->synt == -1)
                return init_token(TOKEN_ERR, "pipe");
            took = init_token(TOKEN_PIPE, "pipe");
            return (took);
         }
        // if (lexer->c == '"')
        // {
        //     took = lexer_collect_string(lexer);
        //     return (took);
        // }
        // // if (lexer->c == 39)
        // if (lexer->c == 39)
        // {
        //     took = lexer_collect_string2(lexer);
        //     return (took);
        // }
        // printf("tokken = %s\n", took->value);
            // return (took);
        // if (isalnum(lexer->c))
            return lexer_collect_id(lexer);
        // if (lexer->c == 39) 
        //     took = lexer_collect_string(lexer);
        // if (lexer->c == '')

    }
    // return NULL;
    return init_token(TOKEN_EOF, "\0");
}

char * lexer_collect_string(t_lexer* lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    // lexer_advance(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    while(lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        // printf ("yeah %c\n", lexer->c);
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
        if (lexer->c == '"')
        {
            s = lexer_get_current_char_as_string(lexer);
            value = ft_strjoin(value, s);
            break;
        }
        // if (lexer->c == '"')
        // {
        //     s = lexer_get_current_char_as_string(lexer);
        //     value = ft_strjoin(value, s);
        //     break;
        // }
        // if  (lexer->line[lexer->i+1] == 39)
        //     break;
        // {
        //     printf("%c\n%c\n%s\n", value[0], value[strlen(value) - 1], value);
        // }
    }
    lexer_advance(lexer);
    if (value[strlen(value) - 1] != '"' || value[1] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        return NULL;
    }
    // printf("value =  %s\n", value);
    return (value);
}

t_token* lexer_collect_id(t_lexer* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
        if (lexer->c == '|' || lexer->c == '>' || lexer->c == '<' || lexer->c == ' ')
            break;
        if (lexer->c != 39 && lexer->c != '"')
        {
            char* s = lexer_get_current_char_as_string(lexer);
            value = ft_strjoin(value, s);
            lexer_advance(lexer);
        }
         if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
            // printf("lexer fhj%lu\n", lexer->i);
            // return (took);
            // lexer_advance(lexer);
        }
        // if (lexer->c == 39)
        else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
            // return (took);
            // lexer_advance(lexer);
        }
        // strcat(value, s);

    }
    return init_token(TOKEN_ID, value);
}

char* lexer_get_current_char_as_string(t_lexer* lexer)
{
    char* str = malloc(sizeof(char)*2);
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}
t_token* init_token(int type, char* value)
{
    t_token* token = malloc(sizeof(t_token));
    token->i++;
    token->type = type;
    token->value = value;
    token->next = NULL;

    return token;
}