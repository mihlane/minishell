/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_main_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:07 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/15 16:17:58 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	frst_cmd(t_envp *my_env, int *fd, t_command *cmd)
{
	char	*path;

	close(fd[0]);
	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
		dup2(cmd->infile, 0);
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	else
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	ex_ecu(path, cmd->cmd, my_env, cmd->outfile);
}

void	one_cmd(t_envp *my_env, t_command *cmd)
{
	char	*path;

	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile != 1)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	ex_ecu(path, cmd->cmd, my_env, cmd->outfile);
}

void	next_cmd(t_envp *my_env, t_pipe *p, int i, t_command *cmd)
{
	p->id[i] = fork();
	if (p->id[i] == -1)
	{
		putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		p->check = -1;
		return ;
	}
	if (p->id[i] == 0)
		ft_norm__(my_env, p, i, cmd);
}

void	last_cmd(t_envp *my_env, int *fd, t_command *cmd)
{
	char	*path;

	close(fd[1]);
	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
		dup2(cmd->infile, 0);
	else
		dup2(fd[0], 0);
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	close(fd[0]);
	close(fd[1]);
	ex_ecu(path, cmd->cmd, my_env, cmd->outfile);
}
