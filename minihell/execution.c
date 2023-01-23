/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/20 20:54:23 by mhabibi-         ###   ########.fr       */
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

void	execution(t_command *list, t_envp *my_env, int i)
{
	handle_signals(SIG_CHILD);
	if (i == 1)
		pipes(my_env->num_pipe, list, my_env);
	handle_signals(SIGINT);
	handle_signals(SIGQUIT);
}
