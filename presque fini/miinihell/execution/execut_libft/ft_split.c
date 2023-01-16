/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 08:03:28 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/02 09:58:35 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

static int	hmuch_calc(char *str, char c)
{
	int	hmuch;
	int	i;

	i = 0;
	hmuch = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		hmuch++;
		while (str[i] && str[i] != c)
		{
			i++;
		}
	}
	return (hmuch);
}

static int	ft_fill(char **arr, char *s, int i, char c)
{
	int	n;
	int	p;

	p = 0;
	while (s[i] == c)
		i++;
	p = i;
	while (s[i] && s[i] != c)
		i++;
	arr[0] = malloc(i - p + 1);
	n = 0;
	while (p < i)
	{
		arr[0][n] = s[p];
		p++;
		n++;
	}
	arr[0][n] = '\0';
	return (i);
}

void	ft_free(char **arr, int m)
{
	if (arr[m] == NULL)
	{
		while (m >= 0)
		{
			free(&arr[m]);
			m--;
		}
		free(arr);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		m;
	int		i;

	m = 0;
	i = 0;
	if (!s)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (hmuch_calc((char *)s, c) + 1));
	if (arr == NULL)
		return (0);
	while (s[i] && m < hmuch_calc((char *)s, c))
	{
		i = ft_fill(&arr[m], (char *)s, i, c);
		ft_free(arr, m);
		m++;
	}
	arr[hmuch_calc((char *)s, c)] = 0;
	return (arr);
}
