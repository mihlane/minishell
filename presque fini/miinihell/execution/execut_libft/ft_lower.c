/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:17:42 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/15 13:29:16 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"
#include <stdio.h>
#include <string.h>
char	*lo_wer(char *s)
{
	int		i;
	char	*low;

	i = 0;
	if (!s)
		return (NULL);
	low = malloc(ft_strlen(s) + 1);
	// printf("helo\n");
	while (s[i])
	{
		if (ft_isalpha(s[i]))
			low[i] = ft_tolower(s[i]);
		else
			low[i] = s[i];
		i++;
	}
	low[i] = 0;
	return (low);
}
