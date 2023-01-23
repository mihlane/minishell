/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:03:34 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/20 20:18:00 by mhabibi-         ###   ########.fr       */
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
