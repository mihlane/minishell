/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:00:35 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:14:55 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "token.h"
#include "lexer.h"

t_token	*lexer_collect_redirect2(t_lexer *lexer)
{
	char	*value;

	value = ft_calloc(1, sizeof(char));
	lexer_advance_skip_ws(lexer);
	if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|' )
		lexer->synt = -1;
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
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
		return (init_token(TOKEN_ERR, value, 1));
	return (init_token(TOKEN_RD2, value, 1));
}

void	advance_one_skws(t_lexer *lexer)
{
	lexer_advance(lexer);
	lexer_skip_whitespace(lexer);
}

t_token	*lexer_collect_redirect1(t_lexer *lexer)
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
		return (init_token(TOKEN_ERR, value, 1));
	return (init_token(TOKEN_RD1, value, 1));
}

char	*collect_doub_sing(t_lexer *lexer, int *z, char *value)
{
	if (lexer->c == '"')
	{
		value = ft_strjoi(value, lexer_collect_string(lexer));
		*z = -1;
	}
	else if (lexer->c == 39)
	{
		value = ft_strjoi(value, lexer_collect_string2(lexer));
		*z = -1;
	}
	return (value);
}

t_token	*lexer_collect_redirect3(t_lexer *lexer)
{
	char	*value;
	int		z;

	z = 1;
	value = ft_calloc(1, sizeof(char));
	lexer_advance_skip_ws(lexer);
	if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|')
		lexer->synt = -1;
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line)
		&& lexer->c != ' ' && lexer->c != 10)
	{
		if (lexer->c == '"' || lexer->c == 39)
			value = collect_doub_sing(lexer, &z, value);
		if (lexer->c == ' ' || lexer->c == 10)
			break ;
		if (lexer->c == '>' || lexer->c == '<' || lexer->c == '|')
			break ;
		else if (lexer->c != 39 && lexer->c != '"')
			value = join1(lexer, value);
	}
	if (value[0] == '\0')
		lexer->synt = -1;
	if (lexer->synt == -1)
		return (init_token(TOKEN_ERR, value, z));
	return (init_token(TOKEN_RD3, value, z));
}
