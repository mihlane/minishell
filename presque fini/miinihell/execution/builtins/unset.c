/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:04 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/08 16:05:34 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	check_unset(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[0]))
		return (0);
	while (var[i])
	{
		if (!ft_isvalid(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ex_unset(char **sp, t_envp *my_env)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	if (sp[1] && sp[1][0] == '-')
	{
		printf("options not required\n");
		my_env->status = 2;
	}
	else
	{
		while (sp[i])
		{
			my_env->status = ft_remove(my_env, sp[i]);
			if (k != 1)
				k = my_env->status;
			i++;
		}
		my_env->status = k;
	}
}
