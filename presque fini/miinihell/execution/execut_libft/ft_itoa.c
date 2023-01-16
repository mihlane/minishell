/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:51:30 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 21:36:38 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

static int	hmch_c(long int n)
{
	long int	p;

	p = 1;
	if (n < 0)
		n = -n;
	while ((n / 10) > 0)
	{
		n = n / 10;
		p += 1;
	}
	return (p);
}

static char	*ft_posfill(char *str, int n, long int r, long int i)
{
	str[r] = '\0';
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	r = r - 1;
	while (n > 0 && r >= i)
	{
		str[r] = (n % 10) + 48;
		n = n / 10;
		r--;
	}
	return (str);
}

static char	*ft_negfill(char *str, int n, long int r, long int i)
{
	n = -n;
	if (!str)
		return (0);
	str[0] = '-';
	i = 1;
	str[r + 1] = '\0';
	if (n == -2147483648)
	{
		n = 214748364;
		str[r] = '8';
		r = r - 1;
	}
	while (n > 0 && r >= i)
	{
		str[r] = (n % 10) + 48;
		n = n / 10;
		r--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	i;
	long int	r;

	i = 0;
	r = hmch_c((long int)n);
	if (n < 0)
	{
		str = malloc(r + 2);
		str = ft_negfill(str, n, r, i);
	}
	else
	{
		str = malloc(r + 1);
		str = ft_posfill(str, n, r, i);
	}
	return (str);
}
