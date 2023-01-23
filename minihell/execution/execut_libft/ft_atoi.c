/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:24:27 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/20 19:18:54 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

static int	my_skip(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		i = i + 1;
		if (str[i - 1] == '-')
			i = -i;
	}
	return (i);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	p;
	long	n;

	p = 1;
	i = my_skip(str);
	if (i < 0)
	{
		i = -i;
		p = -1;
	}
	if (ft_strlen(&str[i]) > 19)
		return (-1);
	n = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	if (n < 0)
		return (-1);
	return (n * p);
}
