/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:01:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:14:38 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "token.h"
#include "lexer.h"

t_token	*lexer_collect_redirect4(t_lexer *lexer)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	advance_one_skws(lexer);
	if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
		lexer->synt = -1;
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line)
		&& lexer->c != ' ' && lexer->c != 10)
	{
		if (lexer->c == '"')
			value = ft_strjoi(value, lexer_collect_string(lexer));
		else if (lexer->c == 39)
			value = ft_strjoi(value, lexer_collect_string2(lexer));
		if (lexer->c == ' ' || lexer->c == 10)
			break ;
		if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
			break ;
			value = join1(lexer, value);
	}
	if (value[0] == '\0')
		lexer->synt = -1;
	if (lexer->synt == -1)
		return (init_token(TOKEN_ERR, value, (int)ft_strlen(value)));
	return (init_token(TOKEN_RD4, value, (int)ft_strlen(value)));
}

char	*lexer_collect_string2(t_lexer	*lexer)
{
	char	*s;
	char	*value;

	value = ft_calloc(1, sizeof(char));
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_strjoi(value, s);
		lexer_advance(lexer);
		if (lexer->c == 39)
		{
			s = lexer_get_current_char_as_string(lexer);
			value = ft_strjoi(value, s);
			break ;
		}
	}
	lexer_advance(lexer);
	if (value[ft_strlen(value) - 1] != 39 || value[1] == '\0')
	{
		lexer->synt = -1;
		return (NULL);
	}
	return (value);
}

t_token	*lexer_collect_pipe(t_token *took, t_lexer *lexer)
{
	lexer_advance(lexer);
	lexer_skip_whitespace(lexer);
	if (lexer->line[lexer->i] == '\0' | lexer->c == '|')
		lexer->synt = -1;
	if (lexer->synt == -1)
		return (init_token(TOKEN_ERR, "pipe", 1));
	took = init_token(TOKEN_PIPE, "pipe", 1);
	return (took);
}
