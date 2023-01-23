/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:09:31 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:20:41 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

t_expand	*expand_single(t_expand *exp)
{
	char	*str;

	str = NULL;
	str = parser_get_current_char_as_string(exp->c);
	exp->expanded = ft_strjoi(exp->expanded, str);
	token_advance(exp);
	while (exp->c != 39)
	{
		str = parser_get_current_char_as_string(exp->c);
		exp->expanded = ft_strjoi(exp->expanded, str);
		token_advance(exp);
	}
	str = parser_get_current_char_as_string(exp->c);
	exp->expanded = ft_strjoi(exp->expanded, str);
	token_advance(exp);
	return (exp);
}

char	*parser_get_current_char_as_string(char c)
{
	char	*str;

	str = alloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*join_itoa(t_expand *exp, int i)
{
	exp->expanded = ft_strjoi(exp->expanded, ft_itoa(i));
	token_advance(exp);
	token_advance(exp);
	return (exp->expanded);
}

t_expand	*amb_rdr(char	*str3, t_expand *exp)
{
	printf("$%s: ambiguous redirect\n", str3);
	g_sts->status = 1;
	exp->syntax = -1;
	return (NULL);
}

t_expand	*expand_norr(t_expand *exp, t_exp *expp, char *str, char *str3)
{
	char	*user;

	user = NULL;
	if (exp->c == '$' && (ft_isalnum(exp->value[exp->i + 1]) == 0))
		exp->expanded = ret_expanded_quote(str, exp);
	else
	{
		token_advance(exp);
		while (ft_isalnum(exp->c) != 0 || exp->c == '_')
			str3 = get_expanded_str2(str, str3, exp);
		user = ft_getenv(expp, str3);
		if (user == NULL && exp->type > 0 && exp->type <= 4)
			return (amb_rdr(str3, exp));
		if (user != NULL)
			exp->expanded = ft_strjoi(exp->expanded, user);
		else
			exp->expanded = ft_strjoi(exp->expanded, "");
		str3[0] = 0;
	}
	return (exp);
}
