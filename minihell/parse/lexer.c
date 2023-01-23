/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:18:27 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:15:20 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "token.h"
#include "./lexer.h"

t_token	*lexer_get_next_token(t_lexer	*lexer)
{
	t_token	*took;

	took = NULL;
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
	{
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace(lexer);
		if (lexer->c == '>' && lexer->line[lexer->i + 1] == '>')
			return (lexer_collect_redirect2(lexer));
		if (lexer->c == '>' && lexer->line[lexer->i + 1] != '>')
			return (lexer_collect_redirect1(lexer));
		if (lexer->c == '<' && lexer->line[lexer->i + 1] == '<')
			return (lexer_collect_redirect3(lexer));
		if (lexer->c == '<' && lexer->line[lexer->i + 1] != '<')
			return (lexer_collect_redirect4(lexer));
		if (lexer->c == '|')
			return (lexer_collect_pipe(took, lexer));
		return (lexer_collect_id(lexer));
	}
	return (init_token(TOKEN_EOF, "\0", 1));
}

char	*lexer_collect_string(t_lexer	*lexer)
{
	char	*s;
	char	*value;

	value = ft_calloc(1, sizeof(char));
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoi(value, s);
		lexer_advance(lexer);
		if (lexer->c == '"')
		{
			s = lexer_get_current_char_as_string(lexer);
			value = ft_strjoi(value, s);
			break ;
		}
	}
	lexer_advance(lexer);
	if (value[ft_strlen(value) - 1] != '"' || value[1] == '\0')
	{
		lexer->synt = -1;
		return (NULL);
	}
	return (value);
}

t_token	*lexer_collect_id(t_lexer	*lexer)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line)
		&& lexer->c != ' ' && lexer->c != 10)
	{
		if (lexer->c == '|' || lexer->c == '>'
			|| lexer->c == '<' || lexer->c == ' ')
			break ;
		if (lexer->c != 39 && lexer->c != '"')
		{
			s = lexer_get_current_char_as_string(lexer);
			value = ft_strjoi(value, s);
			lexer_advance(lexer);
		}
		if (lexer->c == '"')
			value = ft_strjoi(value, lexer_collect_string(lexer));
		else if (lexer->c == 39)
			value = ft_strjoi(value, lexer_collect_string2(lexer));
	}
	return (init_token(TOKEN_ID, value, 1));
}

char	*lexer_get_current_char_as_string(t_lexer	*lexer)
{
	char	*str;

	str = alloc(sizeof(char) * 2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*init_token(int type, char	*value, int z)
{
	t_token	*token;

	token = alloc(sizeof(t_token));
	token->i++;
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->syntax = 1;
	if (z > 0)
		token->herd = 0;
	else
		token->herd = -1;
	return (token);
}
