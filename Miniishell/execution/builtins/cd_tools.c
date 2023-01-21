/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:26:24 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/08 14:28:00 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	fun_a(t_envp *my_env)
{
	char	*fr_ee;

	fr_ee = my_env->pwd;
	ft_add2env(my_env, "PWD+=/..");
	my_env->pwd = ft_strjoin(my_env->pwd, "/..");
	free(fr_ee);
	printf("cd: error retrieving current directory: getcwd: cannot ");
	printf("access parent directories: No such file or directory\n");
	my_env->status = 0;
}

void	fun_b(t_envp *my_env, char old_cwd[256], char cwd[256])
{
	char	*fr_ee;

	if (arr_s(my_env->env, "PWD") != -1)
	{
		fr_ee = ft_strjoin("OLDPWD=", old_cwd);
		ft_add2env(my_env, fr_ee);
		free(fr_ee);
	}
	fr_ee = ft_strjoin("PWD=", cwd);
	ft_add2env(my_env, fr_ee);
	free(fr_ee);
	free(my_env->pwd);
	my_env->pwd = ft_strdup(cwd);
}

void	get_current(char **sp, t_envp *my_env, int k, char *old_cwd)
{
	char	cwd[256];
	char	*fr_ee;

	if (chdir(sp[1]) == 0 && k == 0)
	{
		if (!getcwd(cwd, sizeof(cwd)))
			fun_a(my_env);
		else
			fun_b(my_env, old_cwd, cwd);
	}
	else if (k == 0)
	{
		fr_ee = ft_strjoin("minishell: cd: ", sp[1]);
		perror(fr_ee);
		free(fr_ee);
		my_env->status = 1;
	}
}

int	get_old_body(char **sp, t_envp *my_env, int k)
{
	char	*fr_ee;

	if (sp[1] && sp[1][0] == '.' && ft_strlen(sp[1]) == 1)
	{
		ft_add2env(my_env, "PWD+=/.");
		fr_ee = ft_strjoin("OLDPWD=", my_env->pwd);
		ft_add2env(my_env, fr_ee);
		free(fr_ee);
		fr_ee = my_env->pwd;
		my_env->pwd = ft_strjoin(my_env->pwd, "/.");
		free(fr_ee);
		printf("cd: error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
		my_env->status = 0;
		k++;
	}
	else
		get_current(sp, my_env, 0, my_env->pwd);
	return (k);
}

void	get_old(char **sp, t_envp *my_env)
{
	char	old_cwd[256];
	int		k;

	k = 0;
	if (!getcwd(old_cwd, sizeof(old_cwd)))
		k = get_old_body(sp, my_env, k);
	else
		get_current(sp, my_env, k, old_cwd);
}
