/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:33:47 by rarahhal          #+#    #+#             */
/*   Updated: 2023/01/17 12:23:27 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/execution.h"

t_exp	*lst_last(t_exp *list)
{
	while (list)
	{
		if (!list->next)
			return (list);
		list = list->next;
	}
	return (list);
}

void	add_front(t_exp **list, t_exp *new)
{
	t_exp	*tmp;

	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		if (*list)
		{
			tmp = lst_last(*list);
			tmp->next = new;
		}
		else
			*list = new;
	}
}

t_exp	*ft_getvar(char *env[], t_exp *exp)
{
	int		i;
	int		j;
	char	*str;
	t_exp	*tmp;

	j = 0;
	i = 0;
	while (env[i])
	{
		tmp = malloc(sizeof (t_exp));
		while (env[i][j] && env[i][j] != '=')
			j++;
		str = ft_cpy(env[i], j++);
		tmp->var = ft_strdup(str);
		tmp->value = ft_cpy(&env[i][j], ft_strlen(&env[i][j]));
		add_front(&exp, tmp);
		j = 0;
		i++;
		tmp = NULL;
		free(str);
	}
	return (exp);
}

char	*ft_cpy(char *s, int k)
{
	char	*var;
	int		i;

	i = 0;
	var = malloc(k + 1);
	while (i < k)
	{
		var[i] = s[i];
		i++;
	}
	var[i] = 0;
	return (var);
}

void	fill_env(char *env[], t_envp *my_env)
{
	int	i;
	int	k;

	k = arr_s(env, "OLDPWD");
	if (k == -1)
		my_env->env = (char **)malloc(sizeof(char *) * (arr_size(env) + 2));
	else
		my_env->env = (char **)malloc(sizeof(char *) * (arr_size(env) + 1));
	i = 0;
	while (env[i])
	{
		if (k == -1 && i == 8)
			my_env->env[i] = ft_strdup("OLDPWD");
		else
			my_env->env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env->env[i] = 0;
}
