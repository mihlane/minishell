/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:46 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/18 21:04:26 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	print_ar(char **arr, int out)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (sea_rch(arr[i], '='))
		{
			putstr_fd(arr[i], out);
			write(out, "\n", 1);
		}
		i++;
	}
}

int	rand__(void)
{
	static unsigned long int	next;

	next += 1;
	next = next * 1103515245 + 12345;
	return ((unsigned int)(next / 65536) % 32768);
}

int	arr_s(char **s, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[k] && str[k] != '=')
		k++;
	if (str[k - 1] == '+')
		k--;
	while (s[i])
	{
		j = 0;
		while (s[i][j] && s[i][j] != '=')
			j++;
		if (ft_strncmp(s[i], str, k) == 0 && k == j)
			return (i);
		i++;
	}
	return (-1);
}

char	**spl(char *s)
{
	int		i;
	char	**sp;

	sp = malloc(3 * sizeof (char *));
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	sp[0] = ft_substr(s, 0, i);
	if (s[i] && s[i + 1])
		sp[1] = ft_substr(s, i + 1, ft_strlen(s) - i - 1);
	else
		sp[1] = NULL;
	sp[2] = NULL;
	return (sp);
}

void	arr_cpy(t_envp *my_env, char *str)
{
	char	**s;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = rand__() % (arr_size(my_env->env) + 1);
	s = malloc((arr_size(my_env->env) + 2) * sizeof (char *));
	if (my_env->env[0] == NULL)
		s[i++] = ft_strdup(str);
	while (my_env->env[j])
	{
		if (i == k)
			s[i] = ft_strdup(str);
		else
			s[i] = ft_strdup(my_env->env[j++]);
		i++;
	}
	s[i] = NULL;
	free_arr(my_env->env);
	free(str);
	my_env->env = s;
}

void	arr_delete(t_envp *my_env, char **s, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = arr_s(my_env->env, str);
	while (my_env->env[j])
	{
		if (j == k)
			j++;
		else
			s[i++] = ft_strdup(my_env->env[j++]);
	}
	s[i] = NULL;
}
