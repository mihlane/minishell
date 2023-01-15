/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:44 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 16:18:45 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	sea_rch(char *s, int a)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

size_t	arr_size(char *env[])
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	fill_arr(char *env[], char *s[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		s[i] = ft_strdup(env[i]);
		i++;
	}
	s[i] = 0;
}

int	__sort(char **s)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (ft_strcmp(s[k], s[i]) == 1)
			k = i;
		i++;
	}
	return (k);
}
