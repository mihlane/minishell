/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:15:09 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/10 15:58:52 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_sizelen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	return (i);
}

char	*ft_cut(char *stored)
{
	int		i;
	char	*str;

	i = 0;
	if (!stored[i])
		return (NULL);
	i = ft_sizelen(stored);
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		str[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
	{
		str[i] = stored[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_last_part(char *stored)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	i = ft_sizelen(stored);
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stored) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stored[i])
		str[j++] = stored[i++];
	str[j] = '\0';
	free(stored);
	return (str);
}

char	*r_and_j(int filedes, char *buffer)
{
	char	*str;
	int		c;

	str = malloc(sizeof(char) * 1 + 1);
	if (!str)
		return (NULL);
	c = 1;
	while (c != 0 && !ft_strchr(buffer, '\n'))
	{
		c = read(filedes, str, 1);
		if (c == -1)
		{
			free (str);
			return (NULL);
		}
		str[c] = '\0';
		buffer = ft_strjoin(buffer, str);
	}
	free (str);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*buff;

	if (fd < 0)
		return (0);
	buff = r_and_j(fd, buff);
	if (!buff)
		return (NULL);
	ret = ft_cut(buff);
	buff = ft_last_part(buff);
	return (ret);
}
