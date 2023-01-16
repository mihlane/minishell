/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:40 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/15 13:26:36 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	child(t_pipe *p, int k, t_command *cmd, t_envp *my_env)
{
	if (k > 0)
		multiple_p(p, k, cmd, my_env);
	else
	{
		p->pid1 = fork();
		if (p->pid1 == -1)
			putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		if (p->pid1 == 0)
		{
			if (!is_built(cmd->cmd[0]))
				one_cmd(my_env, cmd);
			else
				exit (0);
		}
		else
		{
			if (!is_built(cmd->cmd[0]))
				main_wait(p, k, my_env, 1);
			__builtins(cmd->cmd, my_env, cmd->outfile, k);
		}
	}
}

int	pipes(int k, t_command *cmd, t_envp *my_env)
{
	t_pipe	*p;
	int		i;

	i = -1;
	p = malloc(sizeof (t_pipe));
	p->check = 0;
	p->fd = malloc(k * sizeof(int *));
	while (++i < k)
		p->fd[i] = malloc(2 * sizeof(int));
	if (k < 0)
		return (0);
	i = -1;
	child(p, k, cmd, my_env);
	while (++i < k)
		free(p->fd[i]);
	free(p->fd);
	free(p);
	return (0);
}
