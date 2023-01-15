/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:15:27 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/14 18:35:22 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	i = -1;
// 	j = 0;
// 	if (!s1)
// 	{
// 		s1 = (char *)malloc(1 * sizeof(char));
// 		s1[0] = '\0';
// 	}
// 	if (!s1 || !s2)
// 		return (NULL);
// 	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (str == NULL)
// 		return (NULL);
// 	if (s1)
// 		while (s1[++i] != '\0')
// 			str[i] = s1[i];
// 	while (s2[j] != '\0')
// 		str[i++] = s2[j++];
// 	str[i] = '\0';
// 	free(s1);
// 	return (str);
// }

// char	*ft_strchr(char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)s + i);
// 		i++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *) s + i);
// 	return (NULL);
// }

// size_t	ft_strlen(char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }
