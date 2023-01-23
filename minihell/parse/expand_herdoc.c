/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 04:21:22 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 17:04:15 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

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
		if (toke[i] == '"' || toke[i] == 39)
			expanded = join_expand_s_d(expanded, toke, &i);
		if (toke[i] && toke[i] != '"' && toke[i] != 39)
			expanded = join_no_doll_and_doll(str, toke, expanded, &i);
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
