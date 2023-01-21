/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:52 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/18 21:04:26 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	*new_var(char *var)
{
	char	*new_var;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(var);
	while (var[i] && var[i] != '=')
		i++;
	if (var[i - 1] == '+')
		j--;
	new_var = malloc(j + 1);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '+')
			i++;
		new_var[j] = var[i];
		j++;
		i++;
	}
	new_var[j] = 0;
	return (new_var);
}

char	*new_value(char *s, char *old)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!sea_rch(old, '='))
		return (ft_substr(s, i, ft_strlen(s) - i));
	return (ft_substr(s, i + 1, ft_strlen(s) - i - 1));
}

char	*get_wich(char *old, char *new, char *ch)
{
	int		i;

	i = 0;
	if (sea_rch(new, '='))
	{
		while (new[i] && new[i] != '=')
			i++;
		if (new[i - 1] == '+' && new[i + 1])
		{
			ch = new_value(new, old);
			new = ft_strjoin(old, ch);
			free(ch);
			return (new);
		}
		else if (new[i - 1] == '+' && !new[i + 1])
		{
			if (sea_rch(old, '='))
				return (ft_strdup(old));
			else
				return (new_var(new));
		}
		return (ft_strdup(new));
	}
	else
		return (ft_strdup(old));
}

int	ft_add2env(t_envp *my_env, char *var)
{
	int		k;
	char	*ch;

	if (!check_export(var))
	{
		var = ft_strjoin("minishell: export: `", var);
		ch = var;
		var = ft_strjoin(var, "': not a valid identifier\n");
		free(ch);
		putstr_fd(var, 2);
		free(var);
		return (1);
	}
	k = arr_s(my_env->env, var);
	if (k != -1)
	{
		ch = my_env->env[k];
		my_env->env[k] = get_wich(my_env->env[k], var, ch);
		free(ch);
	}
	else
		arr_cpy(my_env, new_var(var));
	return (0);
}

int	ft_remove(t_envp *my_env, char *var)
{
	int		k;
	char	**s;

	if (!check_unset(var))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", var);
		return (1);
	}
	if (arr_s(my_env->env, var) == -1)
		return (0);
	k = arr_size(my_env->env);
	s = malloc(k * sizeof (char *));
	arr_delete(my_env, s, var);
	free_arr(my_env->env);
	my_env->env = s;
	return (0);
}
