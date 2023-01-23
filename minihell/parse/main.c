/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:51:25 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 20:54:48 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void	ft_lstclear(t_leak_lst **lst)
{
	t_leak_lst	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if (*lst && (*lst)->content)
			free((*lst)->content);
		if (*lst)
			free(*lst);
		(*lst) = temp;
	}
}

int	get_stx(t_token	*toke)
{
	while (toke)
	{
		if (toke->syntax == -1)
			return (-1);
		toke = toke->next;
	}
	return (1);
}

void	start_minishell(t_token *toke, t_command *cmds, t_envp *my_env, int i)
{
	parse_norm(&toke, &cmds, &my_env);
	i = get_stx(toke);
	my_env->status = g_sts->status;
	execution(cmds, my_env, i);
	g_sts->status = my_env->status;
	my_env->num_pipe = -1;
}

void	minishell(t_token *toke, t_command *cmds, t_envp *my_env)
{
	char	*str;
	int		i;

	i = 0;
	while (1)
	{
		str = readline("~ minishell ");
		handle_signals(SIGINT_);
		if (str == NULL)
		{
			printf("exit\n");
			exit(my_env->status);
		}
		if (str[0])
		{
			add_history(str);
			g_sts->ginp = -1;
		}
		toke = lexi(str);
		if (toke->type != 7 && toke->type != 6 && toke->syntax != -1)
			start_minishell(toke, cmds, my_env, i);
		ft_lstclear(g_sts->leak_lst);
		if (str)
			free(str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_token		*toke;
	t_command	*cmds;
	t_envp		*my_env;

	cmds = NULL;
	toke = NULL;
	g_sts = malloc(sizeof(t_status));
	g_sts->leak_lst = malloc(sizeof(t_leak_lst *));
	*(g_sts->leak_lst) = NULL;
	g_sts->ginp = -1;
	g_sts->status = 0;
	my_env = (t_envp *)malloc(sizeof(t_envp));
	my_env->pwd = getcwd(NULL, 0);
	my_env->status = 0;
	my_env->num_pipe = -1;
	(void)av;
	fill_env(env, my_env);
	handle_signals(SIGINT);
	handle_signals(SIGQUIT);
	disable_ctlc();
	if (ac == 1)
		minishell(toke, cmds, my_env);
	else
		printf("execute as follows: ./minishell (! whith no argument)\n");
	return (my_env->status);
}
