/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:04:37 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 21:37:42 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s01;
	unsigned char	*s02;

	i = 0;
	if (n == 0)
		return (0);
	s01 = (unsigned char *)s1;
	s02 = (unsigned char *)s2;
	while (s01[i] && s02[i] && s01[i] == s02[i] && i < n - 1)
		i++;
	if (s01[i] - s02[i] > 0)
		return (1);
	if (s01[i] - s02[i] < 0)
		return (-1);
	return (0);
}
