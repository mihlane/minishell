/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:53:57 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:14 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

t_command	*create_node(t_token **toke)
{
	t_command	*new_node;
	char		**str;
	int			z;
	int			total_cmds;

	new_node = alloc(sizeof(t_command));
	new_node->next = NULL;
	new_node->infile = 0;
	new_node->outfile = 1;
	new_node->err = 1;
	z = 0;
	total_cmds = get_total_args(*toke);
	str = (char **)alloc(sizeof(char *) * (total_cmds + 1));
	z = fill_struct(toke, new_node, str, 0);
	str[z] = 0;
	new_node->cmd = str;
	return (new_node);
}

void	ft_addback(t_command **node, t_command *new_node)
{
	t_command	*tmp;

	tmp = *node;
	if (*node == NULL)
		*node = new_node;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	tmp->next = new_node;
}

t_command	*ft_init(t_command **node, t_token **token)
{
	t_command	*new_node;
	t_command	*tmp;

	tmp = *node;
	new_node = create_node(token);
	if (new_node->cmd[0])
	{
		if (*node == NULL)
		{
			*node = new_node;
			return (*node);
		}
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_node;
	}
	return (*node);
}

t_command	*init_struct(t_token *toke)
{
	t_token		*tmp;
	t_command	*cmd;
	int			z;

	cmd = NULL;
	z = 0;
	tmp = toke;
	while (tmp)
	{
		ft_init(&cmd, &tmp);
		if (tmp)
			tmp = tmp->next;
		z++;
	}
	return (cmd);
}

char	*expand_double2(char *str, int i)
{
	char	*str3;

	str3 = ft_calloc(1, sizeof(char));
	i++;
	while (str[i])
	{
		if (str[i] == '"')
			break ;
		str3 = ft_strjoi(str3, parser_get_current_char_as_string(str[i]));
		i++;
	}
	return (str3);
}
