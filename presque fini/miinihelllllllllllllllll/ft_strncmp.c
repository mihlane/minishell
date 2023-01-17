/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 21:12:31 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/14 18:24:48 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/execution.h"

int	ft_strncmpp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		// if (s1[i] < 0 || s2[i] < 0)
		// 	return (1);
		if (s1[i] != s2[i])
		{
			// printf("s1-> {%s}, s2->{%s}\n", s1, s2);
			return (1);
		}
		i++;
	}
	return (0);
}
