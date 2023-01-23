/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:24:28 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:35:46 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

t_expand	*expand_nor(t_expand *exp, t_exp *expp)
{
	char	*str;
	char	*user;
	char	*str3;

	str = NULL;
	user = NULL;
	str3 = ft_calloc(1, sizeof(char));
	if (exp->c == '$' && (exp->value[exp->i + 1] == '$'
			|| ft_isdigit(exp->value[exp->i + 1]) != 0))
		check_digits_and_dollar(exp, expp);
	if (exp->c == '$' && exp->value[exp->i + 1] == '?')
		exp->expanded = join_itoa(exp, g_sts->status);
	if (exp->c == '$' && exp->value[exp->i + 1] != '$'
		&& ft_isdigit(exp->value[exp->i + 1]) == 0)
		expand_norr(exp, expp, str, str3);
	return (exp);
}

t_expand	*expand_last_moment(t_expand *exp, t_exp *expp)
{
	char	*str;
	char	*str2;
	char	*user;

	while (exp->c != '\0' && exp->i < (int)strlen(exp->value))
	{
		str2 = ft_calloc(1, sizeof(char));
		token_advance(exp);
		while (ft_isalnum(exp->c) != 0 || exp->c == '_')
		{
			str = parser_get_current_char_as_string(exp->c);
			str2 = ft_strjoi(str2, str);
			token_advance(exp);
		}
		user = ft_getenv(expp, str2);
		if (user == NULL && exp->type > 0 && exp->type <= 4)
		{
			g_sts->status = 1;
			exp->syntax = -1;
			return (NULL);
		}
		if (user != NULL)
			exp->expanded = ft_strjoi(exp->expanded, user);
	}
	return (exp);
}

t_expand	*check_digit_doll2(t_expand *exp, char *str)
{
	if (ft_isdigit(exp->c) != 0)
		token_advance(exp);
	while (ft_isalnum(exp->c) != 0 || exp->c)
		exp->expanded = expand_no_quote(str, exp);
	if (exp->c == '"')
		exp->expanded = expand_no_quote(str, exp);
	return (exp);
}

t_expand	*check_digits_and_dollar(t_expand *exp, t_exp *expp)
{
	char	*str;

	str = NULL;
	while (exp->c != '\0' && exp->i < (int)strlen(exp->value))
	{
		if (exp->c == '$' && exp->value[exp->i + 1] == '?')
		{
			exp->expanded = ft_strjoi(exp->expanded, ft_itoa(g_sts->status));
			token_advance(exp);
			token_advance(exp);
		}
		if (exp->c == '$' && ft_isalpha(exp->value[exp->i + 1]) != 0)
			expand_last_moment(exp, expp);
		if (exp->c == '$')
			token_advance(exp);
		else
			check_digit_doll2(exp, str);
	}
	return (exp);
}

char	*norm1(t_expand *exp, char	*user, t_exp *expp, char	*str)
{
	char	*str2;

	str2 = ft_calloc(1, sizeof(char));
	if (exp->c == '$' && exp->value[exp->i + 1] == '?')
		exp->expanded = dollar_ask(exp);
	if (exp->c == '$' && (ft_isalnum(exp->value[exp->i + 1]) == 0))
	exp->expanded = ret_expanded_quote(str, exp);
	else
	{
		str2 = ft_calloc(1, sizeof(char));
		token_advance(exp);
		while (ft_isalnum(exp->c) != 0 || exp->c == '_')
			str2 = get_expanded_str2(str, str2, exp);
		user = ft_getenv(expp, str2);
		if (user == NULL && exp->type > 0 && exp->type <= 4)
		{
			g_sts->status = 1;
			exp->syntax = -1;
			return (NULL);
		}
		if (user != NULL)
			exp->expanded = ft_strjoi(exp->expanded, user);
	}
	return (str2);
}
