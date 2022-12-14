/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:18:27 by mhabibi-          #+#    #+#             */
/*   Updated: 2022/12/13 12:18:11 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line)  && lexer->c != ' ' && lexer->c != 10)
    {
        // printf ("yeah\n");
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    
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
    // printf ("in in\n");
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
        // printf ("yeah\n");
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    
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
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line)  && lexer->c != ' ' && lexer->c != 10)
    {
        // printf ("yeah\n");
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    
    return init_token(TOKEN_RD3, value);
}
t_token *lexer_collect_redirect4(t_lexer *lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    // lexer_advance(lexer);
    // lexer_advance(lexer);
    lexer_skip_whitespace(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
        // printf ("yeah\n");
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    
    return init_token(TOKEN_RD4, value);
}

t_token* lexer_collect_string2(t_lexer* lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    // lexer_advance(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    // check_num_q(lexer);
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        // printf ("yeah %c\n", lexer->c);
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        if (lexer->c == 39 && lexer->line[lexer->i+1] == ' ')
            break;
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    // printf("value =  %s\n", value);
    return init_token(TOKEN_ID, value);
}

t_token* lexer_get_next_token(t_lexer* lexer)
{
    t_token *took = NULL;
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);


        // else
        if (lexer->c == '>' && lexer->line[lexer->i+1] == '>')
        {
            took = lexer_collect_redirect2(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
        if (lexer->c == '>' && lexer->line[lexer->i+1] != '>')
        {
            took = lexer_collect_redirect1(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
           if (lexer->c == '<' && lexer->line[lexer->i+1] == '<')
        {
            took = lexer_collect_redirect3(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
        if (lexer->c == '<' && lexer->line[lexer->i+1] != '<')
        {
            took = lexer_collect_redirect4(lexer);
            return (took);
            // printf("took = %s\n", took->value);
        }
         if (lexer->c == '|')
         {
            lexer_advance(lexer);
            took = init_token(TOKEN_PIPE, "pipe");
            return (took);
         }
        if (lexer->c == '"')
        {
            took = lexer_collect_string(lexer);
            return (took);
        }
        if (lexer->c == 39)
        if (lexer->c == '"')
        {
            took = lexer_collect_string2(lexer);
            return (took);
        }
        // printf("tokken = %s\n", took->value);
            // return (took);
        // if (isalnum(lexer->c))
            return lexer_collect_id(lexer);
        // if (lexer->c == 39) 
        //     took = lexer_collect_string(lexer);
        // if (lexer->c == '')

        // switch (lexer->c)
        // {
        //     case '|': return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer))); break;
        //     case ';': return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))); break;
        //     case '(': return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); break;
        //     case ')': return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); break;
        //     case '{': return lexer_advance_with_token(lexer, init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer))); break;
        //     case '}': return lexer_advance_with_token(lexer, init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer))); break;
        //     case ',': return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))); break;
        // }
    }
    
    return init_token(TOKEN_EOF, "\0");
}
int check_num_q(t_lexer *lexer)
{
    int i = 0;
    int z = 0;
    while (lexer->line[i])
    {
        if (lexer->line[i] == '"')
            z++;
        if (lexer->line[i] == '|')
            return (z);
        i++;
    }
    return (z);
    
}

t_token* lexer_collect_string(t_lexer* lexer)
{
    char* s;
    char* value = calloc(1, sizeof(char));
    // lexer_advance(lexer);
    // printf("helo\n");
    // printf ("in in\n");
    // check_num_q(lexer);
    while (lexer->c != '\0' && lexer->i < strlen(lexer->line))
    {
        // printf ("yeah %c\n", lexer->c);
        s = lexer_get_current_char_as_string(lexer);
        value = ft_strjoin(value, s);
        // printf ("value : %s\ns is : %s\n", value, s);
        if (lexer->c == '"'  && lexer->line[lexer->i+1] == ' ')
            break;
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    // printf("value =  %s\n", value);
    return init_token(TOKEN_ID, value);
}

t_token* lexer_collect_id(t_lexer* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '\0' && lexer->i < strlen(lexer->line) && lexer->c != ' ' && lexer->c != 10)
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token)
{
    lexer_advance(lexer);

    return token;
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
    token->type = type;
    token->value = value;
    token->next = NULL;

    return token;
}