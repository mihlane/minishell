/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:32:33 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/18 21:04:26 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (&str[0]);
	}
	if (len >= ft_strlen(s))
		str = malloc(ft_strlen(s) + 1);
	else
		str = malloc(len + 1);
	if (str == NULL)
		return (0);
	while (s[i] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
