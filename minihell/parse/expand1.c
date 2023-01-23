/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:08:33 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 17:09:11 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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
