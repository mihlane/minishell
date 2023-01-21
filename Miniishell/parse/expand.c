/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:24:28 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 05:00:08 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*expand_no_quote(char	*str, t_expand	*exp);
char	*ret_expanded_quote(char	*str, t_expand	*exp)
{
	str = parser_get_current_char_as_string(exp->c);
	exp->expanded = ft_strjoi(exp->expanded, str);
	token_advance(exp);
	return (exp->expanded);
}

char	*expand_no_quote(char	*str, t_expand	*exp)
{
	str = parser_get_current_char_as_string(exp->c);
	exp->expanded = ft_strjoi(exp->expanded, str);
	token_advance(exp);
	return (exp->expanded);
}

char	*get_expanded_str2(char *str, char *str2, t_expand *exp)
{
	str = parser_get_current_char_as_string(exp->c);
	str2 = ft_strjoi(str2, str);
	token_advance(exp);
	return (str2);
}
t_exp	*ft_getidx(t_exp *exp, char *s)
{
	t_exp	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(s)) == 0
			&& ft_strlen(s) == ft_strlen(tmp->var))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

char	*ft_getenv(t_exp *exp, char *s)
{
	t_exp	*tmp;

	tmp = ft_getidx(exp, s);
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

t_expand	*check_digits_and_dollar(t_expand *exp, t_exp *expp);

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
	exp->syntax = -1;
	return (NULL);
}

t_expand	*expand_nor(t_expand *exp, t_exp *expp)
{
	char	*str;
	char	*user;
	char	*str3;

	str = NULL;
	user = NULL;
	str3 = ft_calloc(1, sizeof(char));
	if (exp->c == '$' && (exp->value[exp->i + 1] == '$'
			|| isdigit(exp->value[exp->i + 1]) != 0))
		check_digits_and_dollar(exp, expp);
	if (exp->c == '$' && exp->value[exp->i + 1] == '?')
		exp->expanded = join_itoa(exp, g_sts->status);
	if (exp->c == '$' && exp->value[exp->i + 1] != '$'
		&& isdigit(exp->value[exp->i + 1]) == 0)
	{
		if (exp->c == '$' && (isalnum(exp->value[exp->i + 1]) == 0))
			exp->expanded = ret_expanded_quote(str, exp);
		else
		{
			token_advance(exp);
			while (isalnum(exp->c) != 0 || exp->c == '_')
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
	}
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
		while (isalnum(exp->c) != 0 || exp->c == '_')
		{
			str = parser_get_current_char_as_string(exp->c);
			str2 = ft_strjoi(str2, str);
			token_advance(exp);
		}
		user = ft_getenv(expp, str2);
		if (user == NULL && exp->type > 0 && exp->type <= 4)
		{
			printf("$%s: ambiguous redirect\n", str2);
			exp->syntax = -1;
			return (NULL);
		}
		if (user != NULL)
			exp->expanded = ft_strjoi(exp->expanded, user);
	}
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
		if (exp->c == '$' && isalpha(exp->value[exp->i + 1]) != 0)
			expand_last_moment(exp, expp);
		if (exp->c == '$')
			token_advance(exp);
		else
		{
			if (isdigit(exp->c) != 0)
				token_advance(exp);
			while (isalnum(exp->c) != 0 || exp->c)
				exp->expanded = expand_no_quote(str, exp);
			if (exp->c == '"')
				exp->expanded = expand_no_quote(str, exp);
		}
	}
	return (exp);
}



char	*norm1(t_expand *exp,char	*user, t_exp *expp, char	*str)
{
	char	*str2;

	str2 = ft_calloc(1, sizeof(char));
	if (exp->c == '$' && (isalnum(exp->value[exp->i + 1]) == 0))
	{
		str = parser_get_current_char_as_string(exp->c);
		exp->expanded = ft_strjoi(exp->expanded, str);
		token_advance(exp);
	}
	else
	{
		str2 = ft_calloc(1, sizeof(char));
		token_advance(exp);
		while (isalnum(exp->c) != 0 || exp->c == '_')
			str2 = get_expanded_str2(str, str2, exp);
		user = ft_getenv(expp, str2);
		if (user == NULL && exp->type > 0 && exp->type <= 4)
		{
			printf("$%s: ambiguous redirect1\n", str2);
			exp->syntax = -1;
			return (NULL);
		}
		if (user != NULL)
			exp->expanded = ft_strjoi(exp->expanded, user);
	}
	return (str2);
}



char	*expand_double(t_expand *exp, t_exp *expp)
{
	char	*str;
	char	*str2;
	char	*user;

	str = NULL;
	user = NULL;
	exp->expanded = expand_no_quote(str, exp);
	while (exp->c != '\0')
	{
		if (exp->c == '$' && (exp->value[exp->i + 1] == '$'
				|| isdigit(exp->value[exp->i + 1]) != 0))
			check_digits_and_dollar(exp, expp);
		if (exp->c == '$' && exp->value[exp->i + 1] != '$'
			&& isdigit(exp->value[exp->i + 1]) == 0)
			str2 = norm1(exp, user, expp, str);
		else if (exp->c != '$')
		{
			if (exp->c == '"')
				return (ret_expanded_quote(str, exp));
			exp->expanded = expand_no_quote(str, exp);
		}
	}
	if (strlen(str2) == 1)
		return (NULL);
	return (exp->expanded);
}

t_token	*go_expand(t_token *toke, t_exp *expp)
{
	char		*str;
	t_expand	*exp;

	str = NULL;
	exp = init_expand(toke);
	while (exp->c != '\0' && exp->i < (int)strlen(exp->value))
	{
		if (exp->c == '"')
			expand_double(exp, expp);
		if (exp->c == 39)
			expand_single(exp);
		if (exp->c && exp->c != '"' && exp->c != 39)
		{
			if (exp->c != '$')
			{
				str = parser_get_current_char_as_string(exp->c);
				exp->expanded = ft_strjoi(exp->expanded, str);
				token_advance(exp);
			}
			else
				expand_nor(exp, expp);
		}
	}
	if (exp->syntax == -1)
		toke->syntax = -1;
	toke->value = exp->expanded;
	return (toke);
}

t_token	*check_toke(t_token *toke, t_exp *exp)
{
	int	i;

	i = 0;
	while (toke->value[i])
	{
		if (toke->value[i] == '$')
		{
			toke = go_expand(toke, exp);
			break ;
		}
		i++;
	}
	return (toke);
}

void	free_exp(t_exp **lst)
{
	t_exp	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if (*lst && (*lst)->value)
			free((*lst)->value);
		if (*lst && (*lst)->var)
			free((*lst)->var);
		if (*lst)
			free(*lst);
		(*lst) = temp;
	}
}

t_token	*ft_expand(t_token *toke, char **env)
{
	t_token	*tmp;
	t_exp	*exp;

	exp = NULL;
	tmp = NULL;
	exp = ft_getvar(env, exp);
	tmp = toke;
	while (toke)
	{
		if (toke->type != 5 && toke->type != 3)
			toke = check_toke(toke, exp);
		toke = toke->next;
	}
	toke = tmp;
	while (toke)
		toke = toke->next;
	toke = tmp;
	free_exp(&exp);
	return (toke);
}
