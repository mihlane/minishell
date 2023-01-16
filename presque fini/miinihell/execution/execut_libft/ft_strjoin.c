/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:18:17 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 21:37:29 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

static char	*con_cat(char *p, const char *s1, const char *s2)
{	
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s1[y])
	{
		p[x] = s1[y];
		x++;
		y++;
	}
	y = 0;
	while (s2[y])
	{
		p[x] = s2[y];
		x++;
		y++;
	}
	p[x] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		y;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	y = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(y + 1);
	if (p == NULL)
		return (0);
	p = con_cat(p, (char *)s1, (char *)s2);
	return (p);
}
