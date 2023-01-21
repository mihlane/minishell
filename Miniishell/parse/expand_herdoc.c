/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 04:21:22 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 04:16:45 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

char	*check_digitss_and_do(char *exp, int i)
{
	char	*str;
	char	*expanded;

	str = NULL;
	expanded = ft_calloc(1, sizeof(char));
	while (exp[i] != '\0' && i < (int)strlen(exp))
	{
		if (exp[i] == '$')
		{
			str = parser_get_current_char_as_string(exp[i]);
			expanded = ft_strjoi(expanded, str);
			i++;
		}
		else
		{
			if (isdigit(exp[i]) != 0)
				i++;
			while (isalnum(exp[i]) != 0)
			{
				str = parser_get_current_char_as_string(exp[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
			}
			if (exp[i] == '"')
			{
				str = parser_get_current_char_as_string(exp[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
			}
		}
	}
	return (expanded);
}

char	*expand_singlee(char *exp, int i)
{
	char	*str;
	char	*str2;
	char	*user;
	char	*expanded;

	str = NULL;
	str2 = ft_calloc(1, sizeof(char));
	user = NULL;
	expanded = ft_calloc(1, sizeof(char));
	str = parser_get_current_char_as_string(exp[i]);
	expanded = ft_strjoi(expanded, str);
	i++;
	while (exp[i] != '\0')
	{
		if (exp[i] == '$' && (exp[i + 1] == '$' || isdigit(exp[i + 1]) != 0))
		{
			expanded = ft_strjoi(expanded, check_digitss_and_do(exp, i));
			while (exp[i] == '$' || isdigit(exp[i]) != 0)
				i++;
			while (isalnum(exp[i]) != 0)
				i++;
		}
		if (exp[i] == '$' && exp[i + 1] != '$' && isdigit(exp[i + 1]) == 0)
		{
			if (exp[i] == '$' && (isalnum(exp[i + 1]) == 0))
			{
				str = parser_get_current_char_as_string(exp[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
			}
			else
			{
				str2 = ft_calloc(1, sizeof(char));
				i++;
				while (isalnum(exp[i]) != 0)
				{
					str = parser_get_current_char_as_string(exp[i]);
					str2 = ft_strjoi(str2, str);
					i++;
				}
				user = getenv(str2);
				if (user != NULL)
					expanded = ft_strjoi(expanded, user);
			}
		}
		else if (exp[i] != '$')
		{
			if (exp[i] == 39)
			{
				str = parser_get_current_char_as_string(exp[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
				return (expanded);
			}
			str = parser_get_current_char_as_string(exp[i]);
			expanded = ft_strjoi(expanded, str);
			i++;
		}
	}
	if (strlen(str2) == 1)
		return (NULL);
	return (expanded);
}

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
	while (isalnum(exp[i]) != 0)
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

char	*expand_doublee(char *exp, int i)
{
	char	*str;
	char	*str2;
	char	*user;
	char	*expanded;

	str = NULL;
	str2 = ft_calloc(1, sizeof(char));
	user = NULL;
	expanded = ft_calloc(1, sizeof(char));
	str = parser_get_current_char_as_string(exp[i]);
	expanded = ft_strjoi(expanded, str);
	i++;
	while (exp[i] != '\0')
	{
		if (exp[i] == '$' && (exp[i + 1] == '$' || isdigit(exp[i + 1]) != 0))
		{
			expanded = ft_strjoi(expanded, check_digitss_and_do(exp, i));
			while (exp[i] == '$' || isdigit(exp[i]) != 0)
				i++;
			while (isalnum(exp[i]) != 0)
				i++;
		}
		if (exp[i] == '$' && exp[i + 1] != '$' && isdigit(exp[i + 1]) == 0)
		{
			if (exp[i] == '$' && (isalnum(exp[i + 1]) == 0))
			{
				str = parser_get_current_char_as_string(exp[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
			}
			else
			{
				str2 = ft_calloc(1, sizeof(char));
				i++;
				while (isalnum(exp[i]) != 0)
				{
					str = parser_get_current_char_as_string(exp[i]);
					str2 = ft_strjoi(str2, str);
					i++;
				}
				user = getenv(str2);
				if (user != NULL)
					expanded = ft_strjoi(expanded, user);
			}
		}
		else if (exp[i] != '$')
		{
			if (exp[i] == '"')
			{
				str = parser_get_current_char_as_string(exp[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
				return (expanded);
			}
			str = parser_get_current_char_as_string(exp[i]);
			expanded = ft_strjoi(expanded, str);
			i++;
		}
	}
	if (strlen(str2) == 1)
		return (NULL);
	return (expanded);
}

char	*go_expandd(char *toke)
{
	int		i;
	char	*str;
	char	*expanded;

	i = 0;
	str = NULL;
	expanded = ft_calloc(1, sizeof(char));
	while (toke[i] != '\0' && i < (int)strlen(toke))
	{
		if (toke[i] == '"')
		{
			expanded = ft_strjoi(expanded, expand_doublee(toke, i));
			i++;
			while (toke[i] != '"')
				i++;
			i++;
		}
		if (toke[i] == 39)
		{
			expanded = ft_strjoi(expanded, expand_singlee(toke, i));
			i++;
			while (toke[i] != 39)
				i++;
			i++;
		}
		if (toke[i] && toke[i] != '"' && toke[i] != 39)
		{
			if (toke[i] != '$')
			{
				str = parser_get_current_char_as_string(toke[i]);
				expanded = ft_strjoi(expanded, str);
				i++;
			}
			else
			{
				expanded = ft_strjoi(expanded, expand_norre(toke, i));
				i++;
				while (isalnum(toke[i]) != 0)
					i++;
			}
		}
	}
	free(toke);
	toke = expanded;
	return (toke);
}

char	*check_tokee(char *toke, int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (toke[i])
	{
		if (toke[i] == '$')
		{
			str = go_expandd(toke);
			ft_putstr_fd(ft_strjoi(str, "\n"), fd);
			return (str);
		}
		i++;
	}
	ft_putstr_fd(ft_strjoi(toke, "\n"), fd);
	free(toke);
	return (toke);
}

char	*ft_expandd(char *str, int fd)
{
	str = check_tokee(str, fd);
	return (str);
}
