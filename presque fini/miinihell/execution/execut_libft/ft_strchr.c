/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:03:34 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 21:37:13 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	v;

	v = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == v)
			return ((char *)&s[i]);
		i++;
	}
	if (v == '\0')
		return ((char *)&s[i]);
	s = NULL;
	return ((char *)s);
}
