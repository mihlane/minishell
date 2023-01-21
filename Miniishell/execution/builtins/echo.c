/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:56 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/04 14:31:57 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	is_accept(char *s)
{
	int	i;

	i = 1;
	if (s[1] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ex_echo(char **cmd, t_envp *myenv, int out)
{
	int	i;
	int	k;

	i = 1;
	while (cmd[i] && cmd[i][0] == '-')
	{
		if (is_accept(cmd[i]))
			i++;
		else
			break ;
	}
	k = i;
	while (cmd[i])
	{
		putstr_fd(cmd[i], out);
		if (cmd[i + 1])
			write(out, " ", 1);
		i++;
	}
	if (k == 1)
		putstr_fd("\n", out);
	myenv->status = 0;
}
