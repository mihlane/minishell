/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:17 by lsemlali          #+#    #+#             */
/*   Updated: 2023/01/16 16:14:41 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	er_ror(char *err, char *s)
{
	char	*fr;

	if (!access(s, X_OK) || (!access(s, F_OK) && !sea_rch(s, '/'))
		|| (access(s, F_OK) && !sea_rch(s, '/')))
	{
		s = ft_strjoin(s, err);
		fr = ft_strjoin("minishell: ", s);
		putstr_fd(fr, 2);
		free(fr);
	}
	else
	{
		s = ft_strjoin("minishell: ", s);
		perror(s);
	}
	free(s);
}

void	ex_ecu(char *path, char *sp[], t_envp *my_env, int out)
{
	if (is_built(sp[0]))
	{
		__builtins(sp, my_env, out, -1);
		exit (my_env->status);
	}
	else if (execve(path, sp, my_env->env) == -1)
	{
		// printf("path == (%s)\n",sp[0]);
		// if (path)
		// {
		if (sea_rch(sp[0], '/'))
		{
			if (opendir(sp[0]) == NULL)
				er_ror(": No such file or directory\n", sp[0]);
			else
			{
				er_ror(": is a directory\n", sp[0]);
				exit (126);
			}
		}
		else
			er_ror(": Command not found\n", sp[0]);
		exit (127);
		// }
	}
}

void	ft_norm__(t_envp *my_env, t_pipe *p, int i, t_command *cmd)
{
	char	*path;

	close(p->fd[i + 1][0]);
	close(p->fd[i][1]);
	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
		dup2(cmd->infile, 0);
	else
		dup2((*p).fd[i][0], 0);
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	else
		dup2(p->fd[i + 1][1], 1);
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	close(p->fd[i + 1][0]);
	close(p->fd[i + 1][1]);
	ex_ecu(path, cmd->cmd, my_env, cmd->outfile);
}
