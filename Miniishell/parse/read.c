/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:51:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/20 04:14:51 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void	disable_ctlc(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = (char *)alloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = alloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

int	ft_open1(char *str)
{
	int	fd;

	fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		return (-1);
	return (fd);
}

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
	return (fd);
}

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

int	fill_struct(t_token **toke, t_command *nd, char **str, int z)
{
	int	h;

	h = 0;
	while (*toke && (*toke)->type != 5)
	{
		if ((*toke)->syntax == -1)
			nd->err = 0;
		 if ((*toke)->type == 1)
			nd->outfile = ft_open1((*toke)->value);
		if ((*toke)->type == 2)
			nd->outfile = ft_open2((*toke)->value);
		if ((*toke)->type == 3)
			nd->infile = ft_open3((*toke)->value, (*toke)->herd, ++h);
		if ((*toke)->type == 4)
			nd->infile = ft_open4((*toke)->value);
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

char	*expand_single2(char *str, int i)
{
	char	*str2;
	char	*str3;

	str3 = parser_get_current_char_as_string(0);
	i++;
	while (str[i])
	{
		if (str[i] == 39)
			break ;
		str2 = parser_get_current_char_as_string(str[i]);
		str3 = ft_strjoi(str3, str2);
		i++;
	}
	return (str3);
}

int	get_index_double(char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == '"')
			break ;
		i++;
	}
	i++;
	return (i);
}

int	get_index_single(char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] == 39)
			break ;
		i++;
	}
	i++;
	return (i);
}

char	*rmv_quotes_helper(char *value, char *str2)
{
	int	i;

	i = 0;
	while (value[i] && i < (int)ft_strlen(value))
	{
		if (value[i] == 0)
			break ;
		if (value[i] == '"')
		{
			str2 = ft_strjoi(str2, expand_double2(value, i));
			i = get_index_double(value, i);
		}
		if (value[i] && value[i] == 39)
		{
			str2 = ft_strjoi(str2, expand_single2(value, i));
			i = get_index_single(value, i);
		}
		else if (value[i] && value[i] != '"' && value[i] != 39)
			str2 = ft_strjoi(str2,
					parser_get_current_char_as_string(value[i++]));
	}
	return (str2);
}

t_token	*rmv_quotes(t_token *exp)
{
	char	*str2;
	t_token	*tmp;

	str2 = NULL;
	tmp = exp;
	while (tmp)
	{
		if (tmp->value[0])
			str2 = rmv_quotes_helper(tmp->value, str2);
		tmp->value = ft_strdup_p(str2);
		str2 = NULL;
		tmp = tmp->next;
	}
	return (exp);
}

t_token	*fill_stx(t_token *toke)
{
	t_token	*tmp;

	tmp = toke;
	while (toke)
	{
		toke->type = 7;
		toke = toke->next;
	}
	toke = tmp;
	return (toke);
}

void	lexi_helper(t_token	*tmp, t_lexer *lex, t_token *toke)
{
	unsigned int	i;

	i = 0;
	while (toke && i < strlen(lex->line))
	{
		if (toke->type == 7 || toke->syntax == -1 || lex->synt == -1)
		{
			toke = tmp;
			toke = fill_stx(toke);
			printf("syntax error\n");
			break ;
		}
		i++;
		toke = toke->next;
	}
}

t_token	*lexi(char *str)
{
	t_lexer			*lex;
	t_token			*tmp;
	t_token			*toke;

	lex = init_lexer(str);
	lexer_skip_whitespace(lex);
	if (lex->line[lex->i] == '|')
		lex->synt = -1;
	toke = lexer_get_next_token(lex);
	tmp = toke;
	while (toke && lex->i < strlen(lex->line))
	{
		toke->next = lexer_get_next_token(lex);
		toke = toke->next;
	}
	toke = tmp;
	lexi_helper(tmp, lex, toke);
	toke = tmp;
	if (toke == NULL)
		return (NULL);
	return (toke);
}

void	parse_norm(t_token **toke, t_command **cmds, t_envp **my_env)
{
	t_command	*tmp;

	*(toke) = ft_expand(*toke, (*my_env)->env);
	*(toke) = rmv_quotes(*toke);
	*(cmds) = init_struct(*toke);
	(*my_env)->status = g_sts->status;
	tmp = *cmds;
	while (tmp)
	{
		(*my_env)->num_pipe++;
		tmp = tmp->next;
	}
}

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

void	minishell(t_token *toke, t_command *cmds, t_envp *my_env)
{
	char	*str;
	int i;

	i = 0;
	while (1)
	{
		str = readline("~ minishell ");
		handle_signals(SIGINT_);
		if (str == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (str[0])
			add_history(str);
		toke = lexi(str);
		if (toke->type != 7 && toke->type != 6 && toke->syntax != -1)
		{
			parse_norm(&toke, &cmds, &my_env);
			i = get_stx(toke);
			execution(cmds, my_env, i);
			g_sts->status = my_env->status;
			my_env->num_pipe = -1;
		}
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
