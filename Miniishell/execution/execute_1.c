/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:29 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/29 21:56:59 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

t_command	*ex_comm(t_pipe *p, int k, t_command *cmd, t_envp *my_env)
{
	int	i;

	i = -1;
	while (++i < k - 1)
	{
		pipe(p->fd[i + 1]);
		if (p->check == -1)
			return (cmd);
		next_cmd(my_env, p, i, cmd);
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		cmd = cmd->next;
	}
	return (cmd);
}

void	main_wait(t_pipe *p, int k, t_envp *my_env, int ch)
{
	int	i;
	int	st;

	i = 0;
	if (ch == 0)
	{
		f_close(p, k);
		waitpid(p->pid2, &st, 0);
		while (waitpid(p->id[i++], NULL, 0) != -1)
		{
		}
		waitpid(p->pid1, NULL, 0);
	}
	else
		waitpid(p->pid1, &st, 0);
	if (st == 2)
		my_env->status = 130;
	else if (st == 3)
		my_env->status = 131;
	else
		my_env->status = WEXITSTATUS(st);
}

void	main_p(t_pipe *p, int k, t_command *cmd, t_envp *my_env)
{
	cmd = ex_comm(p, k, cmd->next, my_env);
	if (p->check == -1)
	{
		f_close(p, k);
		return ;
	}
	p->pid2 = fork();
	if (p->pid2 == -1)
	{
		putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		return ;
	}
	if (p->pid2 == 0)
		last_cmd(my_env, p->fd[k - 1], cmd);
	else
		main_wait(p, k, my_env, 0);
}

void	multiple_p(t_pipe *p, int k, t_command *cmd, t_envp *my_env)
{
	t_command	*cmds;

	pipe(p->fd[0]);
	cmds = cmd;
	p->pid1 = fork();
	if (p->pid1 == -1)
	{
		putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		return ;
	}
	if (p->pid1 == 0)
		frst_cmd(my_env, p->fd[0], cmds);
	else
		main_p(p, k, cmds, my_env);
}
