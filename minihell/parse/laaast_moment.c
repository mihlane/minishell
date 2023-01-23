/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   laaast_moment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:34:15 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:36:01 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "token.h"
#include "./lexer.h"

char	*dollar_ask(t_expand *exp)
{
	exp->expanded = ft_strjoi(exp->expanded, ft_itoa(g_sts->status));
	token_advance(exp);
	token_advance(exp);
	return (exp->expanded);
}
