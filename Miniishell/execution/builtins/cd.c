/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:54 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/08 14:18:47 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ex_cd(char **sp, t_envp *my_env)
{
	char	*fr_ee;
	char	cwd[256];

	if (sp[1] == NULL || (sp[1][0] == '~' && ft_strlen(sp[1]) == 1))
	{
		if (arr_s(my_env->env, "HOME") == -1 && !sp[1])
		{
			printf("minishell: cd: HOME not set\n");
			my_env->status = 1;
		}
		else
		{
			chdir(getenv("HOME"));
			getcwd(cwd, sizeof(cwd));
			fr_ee = ft_strjoin("PWD=", cwd);
			ft_add2env(my_env, fr_ee);
			free(fr_ee);
		}
	}
	else
		get_old(sp, my_env);
}
