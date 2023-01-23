/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:54:32 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:17 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

char	*expand_single2(char *str, int i)
{
	char	*str2;
	char	*str3;

	str3 = parser_get_current_char_as_string(0);
	i++;
	while (str[i])
	{
		if (str[i] == 39)
			break ;
		str2 = parser_get_current_char_as_string(str[i]);
		str3 = ft_strjoi(str3, str2);
		i++;
	}
	return (str3);
}

int	get_index_double(char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == '"')
			break ;
		i++;
	}
	i++;
	return (i);
}

int	get_index_single(char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == 39)
			break ;
		i++;
	}
	i++;
	return (i);
}

char	*rmv_quotes_helper(char *value, char *str2)
{
	int	i;

	i = 0;
	while (value[i] && i < (int)ft_strlen(value))
	{
		if (value[i] == 0)
			break ;
		if (value[i] == '"')
		{
			str2 = ft_strjoi(str2, expand_double2(value, i));
			i = get_index_double(value, i);
		}
		if (value[i] && value[i] == 39)
		{
			str2 = ft_strjoi(str2, expand_single2(value, i));
			i = get_index_single(value, i);
		}
		else if (value[i] && value[i] != '"' && value[i] != 39)
			str2 = ft_strjoi(str2,
					parser_get_current_char_as_string(value[i++]));
	}
	return (str2);
}

t_token	*rmv_quotes(t_token *exp)
{
	char	*str2;
	t_token	*tmp;

	str2 = NULL;
	tmp = exp;
	while (tmp)
	{
		if (tmp->value[0])
			str2 = rmv_quotes_helper(tmp->value, str2);
		tmp->value = ft_strdup_p(str2);
		str2 = NULL;
		tmp = tmp->next;
	}
	return (exp);
}
