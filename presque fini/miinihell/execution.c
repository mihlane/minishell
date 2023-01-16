/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2023/01/16 14:58:57 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/execution.h"

void	free_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	*ft_skpsp(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] == '\t')
			str[i] = ' ';
		else
			str[i] = s[i];
		i++;
	}
	str[i] = 0;
	free(s);
	return (str);
}

char	**fix_cmd(char **s, int *i)
{
	char	**str;
	char	**sp;
	int		j;
	int		z;

	j = 0;
	z = 0;
	s[*i] = ft_skpsp(s[*i]);
	sp = ft_split(s[*i], ' ');
	str = malloc((arr_size(s) + arr_size(sp)) * sizeof(char *));
	while (j < *i)
	{
		str[j] = ft_strdup(s[j]);
		j++;
	}
	while (sp[z])
		str[j++] = ft_strdup(sp[z++]);
	z = *i + 1;
	*i = j;
	while (s[z])
		str[j++] = ft_strdup(s[z++]);
	str[j] = NULL;
	free_arr(sp);
	free_arr(s);
	return (str);
}

// void	check_list(t_command	**list)
// {
// 	t_command	*tmp;
// 	int			i;

// 	i = 0;
// 	tmp = *list;
// 	while (tmp)
// 	{
// 		i = 0;
// 		if (tmp->madir_walo == -404
// 			|| (ft_strncmp(tmp->cmd[0], "export", 6) == 0
// 				&& ft_strlen(tmp->cmd[0]) == 6))
// 			tmp = tmp->next;
// 		else
// 		{
// 			while (tmp->cmd[i])
// 			{
// 				if (tmp->splite[i] == 1 && sea_rch(tmp->cmd[i], ' '))
// 					tmp->cmd = fix_cmd(tmp->cmd, &i);
// 				else
// 					i++;
// 			}
// 			tmp = tmp->next;
// 		}
// 	}
// }

void	execution(t_command *list, t_envp *my_env)
{
	// handle_signals(SIG_CHILD);
	// check_list(&list);
	
	// printf("{%s}\n", list->cmd[1]);
	// printf("{%s}\n", list->cmd[0]);
	pipes(my_env->num_pipe, list, my_env);

	// handle_signals(SIGINT);
	// handle_signals(SIGQUIT);
}
