/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:48 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/11 11:35:32 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	arr_deletee(char **my_env, char **s, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (my_env[j])
	{
		if (ft_strncmp(my_env[j], str, ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(my_env[j]))
			j++;
		else
			s[i++] = ft_strdup(my_env[j++]);
	}
	free_arr(my_env);
	s[i] = NULL;
}

char	**ft_removee(char *my_env[], char *var)
{
	int		k;
	char	**s;

	k = arr_size(my_env);
	s = malloc(k * sizeof (char *));
	arr_deletee(my_env, s, var);
	return (s);
}

int	get_pr_len(char *s)
{
	size_t	k;

	k = ft_strlen(s) + 11;
	if (sea_rch(s, '='))
		k += 2;
	return (k);
}

void	print_q(char *s, int out)
{
	int		i;
	int		k;
	char	*str;

	str = malloc(get_pr_len(s) + 1);
	i = -1;
	ft_strlcpy(str, "declare -x ", get_pr_len(s));
	k = 11;
	while (s[++i] && s[i] != '=')
		str[k++] = s[i];
	if (s[i])
		str[k++] = s[i];
	if (sea_rch(s, '='))
	{
		str[k++] = '"';
		while (s[++i])
			str[k++] = s[i];
		str[k++] = '"';
	}
	str[k] = '\0';
	putstr_fd(str, out);
	putstr_fd("\n", out);
	free(str);
}

void	export_(char **arr, int out)
{
	int		i;
	int		c;
	char	**s;

	i = 0;
	c = 0;
	s = malloc((arr_size(arr) + 1) * sizeof (char *));
	fill_arr(arr, s);
	while (arr_size(s) > 0)
	{
		c = __sort(s);
		print_q(s[c], out);
		s = ft_removee(s, s[c]);
		i++;
	}
	free(s);
}
