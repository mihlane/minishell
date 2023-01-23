/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:48:37 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/19 14:14:35 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include <stdlib.h>

t_leak_lst	*ft_lstnew(void *content)
{
	t_leak_lst	*list;

	list = malloc(sizeof(t_leak_lst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_front(t_leak_lst	**lst, t_leak_lst	*new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

void	*alloc(size_t size)
{
	void	*content;

	content = malloc(size);
	if (!content)
	{
		perror("");
		exit(1);
	}
	ft_lstadd_front(g_sts->leak_lst, ft_lstnew(content));
	return (content);
}
