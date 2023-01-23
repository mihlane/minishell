/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:53:10 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:12 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int	ft_open4(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY, 0600);
	if (fd == -1)
	{
		g_sts->status = 1;
		perror(str);
		return (-1);
	}
	return (fd);
}

int	get_total_cmds(t_token *toke)
{
	t_token	*tmp;
	int		i;

	tmp = toke;
	i = 0;
	while (toke)
	{
		if (toke->type == 5)
			i++;
		toke = toke->next;
	}
	return (i + 1);
	toke = tmp;
}

int	get_total_args(t_token *toke)
{
	t_token	*tmp;
	int		i;

	tmp = toke;
	i = 0;
	while (tmp)
	{
		if (tmp->type == 5)
			break ;
		if (tmp->type == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	open_files(t_token **toke, t_command *nd, int h)
{
	if ((*toke)->type == 1)
		nd->outfile = ft_open1((*toke)->value);
	if ((*toke)->type == 2)
		nd->outfile = ft_open2((*toke)->value);
	if ((*toke)->type == 3)
		nd->infile = ft_open3((*toke)->value, (*toke)->herd, ++h);
	if ((*toke)->type == 4)
		nd->infile = ft_open4((*toke)->value);
}

int	fill_struct(t_token **toke, t_command *nd, char **str, int z)
{
	int	h;

	h = 0;
	while (*toke && (*toke)->type != 5)
	{
		if ((*toke)->syntax == -1)
			nd->err = 0;
		if ((*toke)->type >= 1 && (*toke)->type <= 4)
			open_files(toke, nd, h);
		if ((*toke)->type == 0)
		{
			str[z] = ft_strdup_p((*toke)->value);
			if (str[z])
				z++;
		}
		if ((*toke)->type == 6)
			break ;
		if ((*toke)->type == 5)
		{
			*toke = (*toke)->next;
			break ;
		}
		*toke = (*toke)->next;
	}
	return (z);
}
