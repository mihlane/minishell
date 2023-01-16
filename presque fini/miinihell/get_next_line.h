/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:15:52 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/14 18:34:44 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
#include "includes/execution.h"

char	*get_next_line(int fd);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strchr(char *s, int c);
// char	*ft_substr(char *str, size_t start, size_t len);
// size_t	ft_strlen(char *s);
// char	*ft_strdup(char *s1);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
