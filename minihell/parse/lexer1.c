/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:59:51 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:15:00 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "token.h"
#include "lexer.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = alloc(sizeof(t_lexer));
	lexer->line = contents;
	lexer->i = 0;
	lexer->c = lexer->line[lexer->i];
	lexer->synt = 1;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
	{
		lexer->i += 1;
		lexer->c = lexer->line[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
	{
		lexer_advance(lexer);
	}
}

void	lexer_advance_skip_ws(t_lexer *lexer)
{
	lexer_advance(lexer);
	lexer_advance(lexer);
	lexer_skip_whitespace(lexer);
}

char	*join1(t_lexer *lexer, char *value)
{
	char	*s;

	s = lexer_get_current_char_as_string(lexer);
	value = ft_strjoi(value, s);
	lexer_advance(lexer);
	return (value);
}
