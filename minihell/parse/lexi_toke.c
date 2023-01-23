/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexi_toke.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 19:13:20 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:14:15 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/lexer.h"
#include "token.h"
#include "../includes/execution.h"

void	token_advance(t_expand *lexer)
{
	if (lexer->c != '\0' && lexer->i < (int)ft_strlen(lexer->value))
	{
		lexer->i += 1;
		lexer->c = lexer->value[lexer->i];
	}
}

void	token_skip_whitespace(t_expand *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
	{
		token_advance(lexer);
	}
}

t_expand	*init_expand(t_token *toke)
{
	t_expand	*expand;

	expand = alloc(sizeof(t_expand));
	expand->value = toke->value;
	expand->i = 0;
	expand->c = expand->value[expand->i];
	expand->expanded = ft_calloc(1, sizeof(char));
	expand->type = toke->type;
	return (expand);
}
