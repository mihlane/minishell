/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:51:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:14:05 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

t_token	*fill_stx(t_token *toke)
{
	t_token	*tmp;

	tmp = toke;
	while (toke)
	{
		toke->type = 7;
		toke = toke->next;
	}
	toke = tmp;
	return (toke);
}

void	lexi_helper(t_token	*tmp, t_lexer *lex, t_token *toke)
{
	unsigned int	i;

	i = 0;
	while (toke && i < ft_strlen(lex->line))
	{
		if (toke->type == 7 || toke->syntax == -1 || lex->synt == -1)
		{
			toke = tmp;
			toke = fill_stx(toke);
			printf("syntax error\n");
			g_sts->status = 258;
			break ;
		}
		i++;
		toke = toke->next;
	}
}

t_token	*lexi(char *str)
{
	t_lexer			*lex;
	t_token			*tmp;
	t_token			*toke;

	lex = init_lexer(str);
	lexer_skip_whitespace(lex);
	if (lex->line[lex->i] == '|')
		lex->synt = -1;
	toke = lexer_get_next_token(lex);
	tmp = toke;
	while (toke && lex->i < ft_strlen(lex->line))
	{
		toke->next = lexer_get_next_token(lex);
		toke = toke->next;
	}
	toke = tmp;
	lexi_helper(tmp, lex, toke);
	toke = tmp;
	if (toke == NULL)
		return (NULL);
	return (toke);
}

void	parse_norm(t_token **toke, t_command **cmds, t_envp **my_env)
{
	t_command	*tmp;

	*(toke) = ft_expand(*toke, (*my_env)->env);
	*(toke) = rmv_quotes(*toke);
	*(cmds) = init_struct(*toke);
	(*my_env)->status = g_sts->status;
	tmp = *cmds;
	while (tmp)
	{
		(*my_env)->num_pipe++;
		tmp = tmp->next;
	}
}
