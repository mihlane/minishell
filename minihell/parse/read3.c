/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:52:43 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 20:54:54 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int	ft_open2(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	size(char *str, char *del)
{
	int	s;
	int	d;

	s = ft_strlen(str);
	d = ft_strlen(del);
	if (d > s)
		return (d);
	return (s);
}

char	*remove_new_line(char *line)
{
	char	*s;
	int		i;

	s = alloc(ft_strlen(line) * sizeof(char));
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		s[i] = line[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	fun(int fd, char *delimeter, int i)
{
	char	*line;
	char	*tmp;

	(void)fd;
	handle_signals(SIGHEREDOC);
	line = readline("");
	while (line)
	{
		tmp = remove_new_line(line);
		if (!ft_strncmpp(tmp, delimeter) || !line)
		{
			if (!line && g_sts->status != 1)
				g_sts->ginp = SIGHEREDOC;
			free(line);
			break ;
		}
		if (i != -1)
			line = ft_expandd(line, fd);
		else
		{
			ft_putstr_fd(ft_strjoi(line, "\n"), fd);
			free (line);
		}
		line = readline("");
	}
}

int	ft_open3(char *str, int i, int h)
{
	int		fd;
	char	*s;

	s = ft_strjoi(str, ft_itoa(h));
	fd = open(ft_strjoi("/tmp/", s), O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	fun(fd, str, i);
	if (g_sts->status == 1)
	{
		dup2(g_sts->ginp, 0);
		return (-1);
	}
	(void)i;
	fd = open(ft_strjoi("/tmp/", s), O_RDONLY, 0777);
	g_sts->ginp = 1;
	return (fd);
}
