/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:25 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/15 01:38:49 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*f_check(char **sp, char *tmp, char *s)
{
	char	*n_cmd;
	int		i;

	i = -1;
	while (sp[++i])
	{
		n_cmd = ft_strjoin(sp[i], tmp);
		if (!access(n_cmd, F_OK) && !access(n_cmd, X_OK))
		{
			free_arr(sp);
			free(tmp);
			free(s);
			return (n_cmd);
		}
		free(n_cmd);
		n_cmd = NULL;
	}
	free_arr(sp);
	free(tmp);
	free(s);
	return (0);
}

char	*get_path(char *s, char *cmd)
{
	char	**sp;
	char	*tmp;

	printf("{%s}\n", cmd);
	if (sea_rch(cmd, '/'))
	{
		free(s);
		return (cmd);
	}
	if (!s)
		return (NULL);
	sp = ft_split(s, ':');
	tmp = ft_strjoin("/", cmd);
	return (f_check(sp, tmp, s));
}

char	*handle_env(char *env[])
{
	char	*s;
	int		i;

	i = 0;
	while (env[i])
	{
		s = ft_substr(env[i], 0, 5);
		if (ft_strncmp("PATH=", s, 5) == 0)
		{
			free (s);
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		}
		free (s);
		i++;
	}
	return (NULL);
}
