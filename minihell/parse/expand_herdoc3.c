/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:01:55 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:20:11 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

char	*expand_norre(char *exp, int i)
{
	char	*str;
	char	*expanded;
	char	*user;
	char	*str3;

	str = NULL;
	expanded = ft_calloc(1, sizeof(char));
	user = NULL;
	str3 = ft_calloc(1, sizeof(char));
	i++;
	while (ft_isalnum(exp[i]) != 0)
	{
		str = parser_get_current_char_as_string(exp[i]);
		str3 = ft_strjoi(str3, str);
		i++;
	}
	user = getenv(str3);
	if (user != NULL)
		expanded = ft_strjoi(expanded, user);
	str3[0] = 0;
	return (expanded);
}

char	*str_expanded(char *str, char *exp, int *i, char *expanded)
{
	str = parser_get_current_char_as_string(exp[(*i)]);
	expanded = ft_strjoi(expanded, str);
	(*i)++;
	return (expanded);
}

char	*expand_doublee(char *exp, int i)
{
	char	*str;
	char	*str2;
	char	*expanded;

	str = NULL;
	str2 = ft_calloc(1, sizeof(char));
	expanded = ft_calloc(1, sizeof(char));
	expanded = str_expanded(str, exp, &i, expanded);
	while (exp[i] != '\0')
	{
		if (exp[i] == '$' && (exp[i + 1] == '$' || ft_isdigit(exp[i + 1]) != 0))
			expanded = get_expanded_2doll_dig(expanded, exp, &i);
		if (exp[i] == '$' && exp[i + 1] != '$' && ft_isdigit(exp[i + 1]) == 0)
			expanded = dollar_odamo_digit(expanded, str2, &i, exp);
		else if (exp[i] != '$')
		{
			if (exp[i] == '"')
				return (str_expanded(str, exp, &i, expanded));
			expanded = str_expanded(str, exp, &i, expanded);
		}
	}
	if (strlen(str2) == 1)
		return (NULL);
	return (expanded);
}

char	*join_expand_s_d(char *expanded, char *toke, int *i)
{
	if (toke[*i] == '"')
	{
		expanded = ft_strjoi(expanded, expand_doublee(toke, *i));
		(*i)++;
		while (toke[*i] != '"')
			(*i)++;
		(*i)++;
	}
	if (toke[*i] == 39)
	{
		expanded = ft_strjoi(expanded, expand_singlee(toke, *i));
		(*i)++;
		while (toke[*i] != 39)
			(*i)++;
		(*i)++;
	}
	return (expanded);
}

char	*join_no_doll_and_doll(char *str, char *toke, char *expanded, int *i)
{
	if (toke[(*i)] != '$')
	{
		str = parser_get_current_char_as_string(toke[(*i)]);
		expanded = ft_strjoi(expanded, str);
		(*i)++;
	}
	else
	{
		expanded = ft_strjoi(expanded, expand_norre(toke, (*i)));
		(*i)++;
		while (ft_isalnum(toke[(*i)]) != 0)
			(*i)++;
	}
	return (expanded);
}
