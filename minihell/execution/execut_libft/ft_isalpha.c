/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:19:22 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/04 11:32:55 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

int	is_str(char *s)
{
	int	i;

	if (ft_atoi(s) == -1)
		return (0);
	i = 0;
	while (s[i])
	{
		if (i == 0 && (s[i] == '-' || s[i] == '+'))
			i++;
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
