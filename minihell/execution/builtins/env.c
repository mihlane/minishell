/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:58 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 16:18:59 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ex_env(char **sp, t_envp *my_env, int out)
{
	if (sp[1] == NULL)
		print_ar(my_env->env, out);
	else
		printf("options or arguments not required\n");
	my_env->status = 0;
}
