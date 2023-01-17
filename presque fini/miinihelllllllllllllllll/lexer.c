/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:18:27 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/17 12:28:57 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/execution.h"

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
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("synatx error\n");
            lexer->synt = -1;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
           if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
        }
        if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        lexer_advance(lexer);
    }
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value, 1);
        
    return init_token(TOKEN_RD2, value, 1);
}

t_token *lexer_collect_redirect1(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("synatx error\n");
            return NULL;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
         if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
        }
        if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        lexer_advance(lexer);
    }
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value, 1);
    return init_token(TOKEN_RD1, value, 1);
}

t_token *lexer_collect_redirect3(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    int z = 1;
    lexer_advance(lexer);
    lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("syntax error\n");
            lexer->synt = -1;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line)  && lexer->c != ' ' && lexer->c != 10)
    {
           if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
            z = -1;
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
            z = -1;
        }
         if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        else if (lexer->c != 39 && lexer->c != '"')
        {
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        lexer_advance(lexer);
        }
    }
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value, z);
    return init_token(TOKEN_RD3, value, z);
}

t_token *lexer_collect_redirect4(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));

    lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        {
            printf("synatx error\n");
            lexer->synt = -1;
        }
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
           if (lexer->c == '"')
        {
            value =  ft_strjoin( value, lexer_collect_string(lexer));
        }
       else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
        }
        if (lexer->c == ' ' || lexer->c == 10)
        break;
        if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
        break;
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        lexer_advance(lexer);
    }
    if (value[0] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
    }
    if (lexer->synt == -1)
        return init_token(TOKEN_ERR, value, (int)ft_strlen(value));
    return init_token(TOKEN_RD4, value, (int)ft_strlen(value));
}

char * lexer_collect_string2(t_lexer* lexer)
{
char* s;
    char* value = calloc(1, sizeof(char));
    
    while(lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        lexer_advance(lexer);
        if (lexer->c == 39)
        {
            s = lexer_get_current_char_as_string(lexer);
            value = ft_strjoin(value, s);
            break;
        }
    }
    lexer_advance(lexer);
    if (value[strlen(value) - 1] != 39 || value[1] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        return NULL;
    }
    return (value);
}

t_token* lexer_get_next_token(t_lexer* lexer)
{
    t_token *took = NULL;            
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);
        if (lexer->c == '>' && lexer->line[lexer->i+1] == '>')
        {
            took = lexer_collect_redirect2(lexer);
            return (took);
        }
        if (lexer->c == '>' && lexer->line[lexer->i+1] != '>')
        {
            took = lexer_collect_redirect1(lexer);
            return (took);
        }
           if (lexer->c == '<' && lexer->line[lexer->i+1] == '<')
        {
            took = lexer_collect_redirect3(lexer);
            return (took);
        }
        if (lexer->c == '<' && lexer->line[lexer->i+1] != '<')
        {
            took = lexer_collect_redirect4(lexer);
            return (took);
        }
         if (lexer->c == '|')
         {
            lexer_advance(lexer);
            lexer_skip_whitespace(lexer);
            if (lexer->line[lexer->i] == '\0')
            {
                printf("syntax error\n");
                lexer->synt = -1;
            }
            if (lexer->synt == -1)
                return init_token(TOKEN_ERR, "pipe", 1);
            took = init_token(TOKEN_PIPE, "pipe", 1);
            return (took);
         }
            return lexer_collect_id(lexer);
    }
    return init_token(TOKEN_EOF, "\0", 1);
}

char * lexer_collect_string(t_lexer* lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    
    while(lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        lexer_advance(lexer);
        if (lexer->c == '"')
        {
            s = lexer_get_current_char_as_string(lexer);
            value = ft_strjoin(value, s);
            break;
        }
    }
    lexer_advance(lexer);
    if (value[strlen(value) - 1] != '"' || value[1] == '\0')
    {
        printf("syntax error\n");
        lexer->synt = -1;
        return NULL;
    }
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
        }
        else if  (lexer->c == 39)
        {
            value =  ft_strjoin( value, lexer_collect_string2(lexer));
        }
    }
    return init_token(TOKEN_ID, value, 1);
}

char* lexer_get_current_char_as_string(t_lexer* lexer)
{
    char* str = malloc(sizeof(char)*2);
    str[0] = lexer->c;
    str[1] = '\0';
    return str;
}

t_token* init_token(int type, char* value, int z)
{
    t_token* token = malloc(sizeof(t_token));
    token->i++;
    token->type = type;
    token->value = value;
    token->next = NULL;
    if (z > 0)
        token->herd = 0;
    else
        token->herd = -1;
    return token;
}