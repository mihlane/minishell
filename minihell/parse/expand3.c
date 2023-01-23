/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:10:25 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:17:13 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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
				|| ft_isdigit(exp->value[exp->i + 1]) != 0))
			check_digits_and_dollar(exp, expp);
		if (exp->c == '$' && exp->value[exp->i + 1] != '$'
			&& ft_isdigit(exp->value[exp->i + 1]) == 0)
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
				exp->expanded = ret_expanded_quote(str, exp);
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
