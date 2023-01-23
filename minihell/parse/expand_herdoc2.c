/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:00:46 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:28:36 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

char	*join_i_plus(char *str, char *expanded, int *i, char *exp)
{
	str = parser_get_current_char_as_string(exp[(*i)]);
	expanded = ft_strjoi(expanded, str);
	(*i)++;
	return (expanded);
}

char	*check_digitss_and_do(char *exp, int i)
{
	char	*str;
	char	*expanded;

	str = NULL;
	expanded = ft_calloc(1, sizeof(char));
	while (exp[i] != '\0' && i < (int)strlen(exp))
	{
		if (exp[i] == '$')
			expanded = join_i_plus(str, expanded, &i, exp);
		else
		{
			if (ft_isdigit(exp[i]) != 0)
				i++;
			while (ft_isalnum(exp[i]) != 0)
				expanded = join_i_plus(str, expanded, &i, exp);
			if (exp[i] == '"')
				expanded = join_i_plus(str, expanded, &i, exp);
		}
	}
	return (expanded);
}

char	*dollar_odamo_digit(char *expanded, char *str2, int *i, char *exp)
{
	char	*user;
	char	*str;

	if (exp[(*i)] == '$' && (ft_isalnum(exp[(*i) + 1]) == 0))
	{
		str = parser_get_current_char_as_string(exp[(*i)]);
		expanded = ft_strjoi(expanded, str);
		(*i)++;
	}
	else
	{
		str2 = ft_calloc(1, sizeof(char));
		(*i)++;
		while (ft_isalnum(exp[(*i)]) != 0)
		{
			str = parser_get_current_char_as_string(exp[(*i)]);
			str2 = ft_strjoi(str2, str);
			(*i)++;
		}
		user = getenv(str2);
		if (user != NULL)
			expanded = ft_strjoi(expanded, user);
	}
	return (expanded);
}

char	*get_expanded_2doll_dig(char *expanded, char *exp, int *i)
{
	expanded = ft_strjoi(expanded, check_digitss_and_do(exp, (*i)));
	while (exp[(*i)] == '$' || ft_isdigit(exp[(*i)]) != 0)
		(*i)++;
	while (ft_isalnum(exp[(*i)]) != 0)
		(*i)++;
	return (expanded);
}

char	*expand_singlee(char *exp, int i)
{
	char	*str;
	char	*str2;
	char	*expanded;

	str = NULL;
	str2 = ft_calloc(1, sizeof(char));
	expanded = ft_calloc(1, sizeof(char));
	expanded = join_i_plus(str, expanded, &i, exp);
	while (exp[i] != '\0')
	{
		if (exp[i] == '$' && (exp[i + 1] == '$' || ft_isdigit(exp[i + 1]) != 0))
			expanded = get_expanded_2doll_dig(expanded, exp, &i);
		if (exp[i] == '$' && exp[i + 1] != '$' && ft_isdigit(exp[i + 1]) == 0)
			expanded = dollar_odamo_digit(expanded, str2, &i, exp);
		else if (exp[i] != '$')
		{
			if (exp[i] == 39)
				return (join_i_plus(str, expanded, &i, exp));
			expanded = join_i_plus(str, expanded, &i, exp);
		}
	}
	if (strlen(str2) == 1)
		return (NULL);
	return (expanded);
}
