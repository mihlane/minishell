/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 01:51:11 by mhabibi-          #+#    #+#             */
/*   Updated: 2023/01/13 03:21:55 by mhabibi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include "token.h"

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
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	// free(s2);
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

int ft_open1(char *str)
{
    int fd;
    fd = open(str, O_RDONLY | O_CREAT);
    if (fd == -1)
        return (-1);
    return (fd);
    
}
int ft_open2(char *str)
{
    int fd;
    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (-1);
    return (fd);
    
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int size(char *str, char *del)
{
    int s = ft_strlen(str);
    int d = ft_strlen(del);
    if (d > s)
        return d;
    return s;
}

void    fun(int fd, char *delimeter, int i)
{
    char    *line;

    line = get_next_line(0);
    while (line)
    {
        if ((strcmp(line, delimeter) && (strlen (line)- 1 == strlen(delimeter))) || !line[0])
            break ;
        if (i != -1)
        {
            printf("a\n");
            line = ft_expandd(line);
        }
        ft_putstr_fd(line, fd);
        free (line);
        line = get_next_line(0);
    }
}

int ft_open3(char *str, int i)
{
    int fd;
    fd = open(ft_strjoin2("/tmp/", str),  O_CREAT | O_WRONLY);
    if (fd == -1)
        return (-1);
    fun(fd, str, i);
    return (fd);
    
}
int ft_open4(char *str)
{
    int fd;
    printf("file discriptor kayn hna \n");
    fd = open(str, O_RDONLY | O_CREAT);
    if (fd == -1)
        return (-1);
    return (fd);
    
}

int get_total_cmds(t_token *toke)
{
    t_token *tmp = toke;
    // char **str;
    int i = 0;
    // int z = 0;
    while (toke)
    {
        if (toke->type == 5)
            i++;
        // if (toke->type == 0)
        //     i++;
        toke = toke->next;
    }
    printf("------------%d\n", i);
    return (i + 1);
    toke = tmp;
    // str = malloc(sizeof(char*) * i);
    // while (toke && z < i)
    // {
    //     if (toke->type == 0)
    //         strdup()
    //     toke = toke->next;
    // }
}
int get_total_args(t_token *toke)
{
    t_token *tmp = toke;
    int i = 0;
    while (tmp)
    {
        if (tmp->type == 5)
            break;
        if (tmp->type == 0)
            i++;
        tmp = tmp->next;
    }
    return i;  
}

char **get_cmd(t_token **toke)
{
    // t_token *tmp = toke;
    char **str;
    int z = 0;
    int total_cmds = get_total_args(*toke);
    str = (char **)malloc(sizeof(char*) * (total_cmds  + 1));
    while (*toke && z < total_cmds)
    {
        if ((*toke)->type == 0)
        {
            str[z] = strdup((*toke)->value);
            printf("str ============================== %s\n", str[z]);
            z++;
        }
        // if (toke->type == 5)
        //     cmd = cmd->next;
        *toke = (*toke)->next;
    }
    str[z] = NULL;
    // z = 0;
    // while (z++ < i - 1)
    //     printf("str ============================== %s\n", str[z]);
    return (str);
}


t_command	*create_node(t_token **toke)
{
	t_command	*new_node;
       char **str;
       
	new_node = malloc(sizeof(t_command));
	new_node->next = NULL;
    new_node->infile = -2;
    new_node->outfile = -2;
    int z = 0;
    int total_cmds = get_total_args(*toke);
    str = (char **)malloc(sizeof(char*) * (total_cmds  + 1));
    while (*toke && (*toke)->type != 5)
    {
        // printf("dfk token type= %d\n", (*toke)->type);
            // printf("dk-----------------------khal hna\n");
        if ((*toke)->type == 1)
            new_node->outfile = ft_open1((*toke)->value);
        if ((*toke)->type == 2)
        {
            new_node->outfile = ft_open2((*toke)->value);
        }
        if ((*toke)->type == 3)
            new_node->infile = ft_open3((*toke)->value, (*toke)->herd);
        if ((*toke)->type == 4)
           new_node->infile = ft_open4((*toke)->value);
        if ((*toke)->type == 0)
        {
            str[z] = strdup((*toke)->value);
            // printf("str ============================== %s\n", str[z]);
            z++;
        }
        if ((*toke)->type == 6)
            break;
        //     cmd = cmd->next;
        *toke = (*toke)->next;
    }
	new_node->cmd = str;
	return (new_node);
}

t_command	*ft_init(t_command **node, t_token **token)
{
	t_command	*new_node;
	t_command	*tmp;
    tmp = *node;
	new_node = create_node(token);
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
    return (*node);
}

t_command *init_struct(t_token *toke)
{
    t_token *tmp;
    t_command *cmd = NULL;
    // int total_cmds = get_total_cmds(toke);
    // printf("Toatal Cmds: %d\n", total_cmds);

    // while (total_cmds--)
    // {
    //     ft_init(&cmd);
    // }  
    
    // tmp2 = cmd;

    // open files
    tmp = toke;
    while (tmp)
    {
        
        // if (tmp->type == 1)
        //     cmd->outfile = ft_open1(tmp->value);
        // if (tmp->type == 2)
        //     cmd->outfile = ft_open2(tmp->value);
        // if (tmp->type == 3)
        //     cmd->infile = ft_open3(tmp->value);
        // if (tmp->type == 4)
        //    cmd->infile = ft_open4(tmp->value);
        // if (tmp->type == 0)
        // {
        // printf(" I am HERE !!\n");
            ft_init(&cmd, &tmp);
        // }÷
        if (tmp)
            tmp = tmp->next;
    }
    // printf("{%s}\n", cmd->cmd[0]);
    // cmd = tmp2;
//    int f = 0;
//     while (cmd)
//     {
//         printf("cmd: %d ==> |", f);
//         int i = 0;
//         while (cmd->cmd[i])
//             printf("%s ", cmd->cmd[i++]);
//         printf("|\n");
//         cmd = cmd->next;
//         f++;
//     }
    return (cmd);
}

char *expand_double2(char *str, int i)
{
    char *str2;
    char *str3;
    str3 = parser_get_current_char_as_string(0);
    i++;
    while (str[i])
    {
        if (str[i] == '"')
            break;
        str2 = parser_get_current_char_as_string(str[i]);
        str3 = ft_strjoin(str3, str2);
        i++;
    }
    return (str3);
    
}
char *expand_single2(char *str, int i)
{
    char *str2;
    char *str3;
    str3 = parser_get_current_char_as_string(0);
    i++;
    while (str[i])
    {
        if (str[i] == 39)
            break;
        str2 = parser_get_current_char_as_string(str[i]);
        str3 = ft_strjoin(str3, str2);
        i++;
    }
    return (str3);
    
}

int get_index_double(char *str, int i)
{
    i++;
    while (str[i])
        {
            if (str[i] == '"')
                break;
            i++;
        }
        i++;
        return (i);
}
int get_index_single(char *str, int i)
{
    i++;
    while (str[i])
        {
            if (str[i] == 39)
                break;
            i++;
        }
        i++;
        return (i);
}

t_token *rmv_quotes(t_token *exp)
{
    // int k;
    int i = 0;
    // int z = 0;
    char *str2 = NULL;
    t_token *tmp;
    tmp = exp;
    // exp = exp->next;
    while (exp)
    {
    i = 0;
    // z = 0;
    while (exp->value[i] && i < (int)strlen(exp->value))
    {
        if (exp->value[i] == 0)
            break;
        if (exp->value[i] == '"')
        {
            str2 = ft_strjoin(str2, expand_double2(exp->value, i));
            i = get_index_double(exp->value,i);
            printf("%d\n", i);
        }
        if (exp->value[i] && exp->value[i] == 39)
        {
            str2 = ft_strjoin(str2, expand_single2(exp->value, i));
            i = get_index_single(exp->value, i);
        }
        else if (exp->value[i] && exp->value[i] != '"' && exp->value[i] != 39)
            {
                str2 = ft_strjoin(str2, parser_get_current_char_as_string(exp->value[i]));
                i++;
            }
        printf("str2 ==== %s i = %d\n", str2, i);
        // i++;
    }
    // k = i - z;
    printf("quooooots %s\n", exp->value);
    // str2 = malloc(sizeof(char) * ((i - z) + 1));
    // i = 0;
    // z = 0;
    // while (z < k)
    // {
    //     if (exp->value[i] != '"' && exp->value[i] != 39)
    //     {
    //         str2[z] = exp->value[i];
    //         z++;
    //         i++;
    //     }
    //     else
    //         i++;
    // }
    // str2[i] = 0;
    // printf("toke after removing = %s\n", str2);
    exp->value = str2;
    exp = exp->next;
    }
    exp = tmp;
    return (exp);
    
}




t_token *fill_stx(t_token *toke)
{
    t_token *tmp;
    tmp = toke;
    while (toke)
    {
        toke->type = 7;
        toke = toke->next;
    }
    toke = tmp;
    return (toke);
}
t_token    *lexi(char *str)
{
    unsigned long i = 0;
    t_lexer *lex;
    t_token *tmp;
    t_token *toke;
    lex = init_lexer(str);
    lexer_skip_whitespace(lex);
    if (lex->line[lex->i] == '|')
    {
        printf("syntax error habibi\n");
        lex->synt = -1;
        // return NULL;
    }
    toke = lexer_get_next_token(lex);
    tmp = toke;
    while (toke && lex->i < strlen(lex->line))
    {
        toke->next = lexer_get_next_token(lex);
        toke = toke->next;
    }
    toke = tmp;
    // check_syntax_err(toke);
    i = 0;
    while (toke && i < strlen(lex->line))
    {
        if (toke->type == 6 || toke->type == 7)
        {
            toke = tmp;
            toke = fill_stx(toke);
            printf("syntax error habibiiiiiiiiii\n");
            break;
        }
        // if (toke->value == NULL)
        // {
        //     printf("syntax error habibi\n");
        //     lex->synt = -1;
        //     return NULL;
        // }
        // printf("token  = %s token type %d \n", toke->value, toke->type);
        // printf("token next = %d\n", toke->type);
        // printf("token next = %s\n", toke->value);
        i++;
        toke = toke->next;
    }
    toke = tmp;
    if (toke == NULL)
        return (NULL);
    return (toke);
    // printf("tokken = %s\n", toke->value);
    // printf("token next = %s\n", toke->next->value);
}
int main(int ac, char **av)
{
    char *str;
    t_token *toke;
    t_command *cmds = NULL;
    // t_expand *exp = NULL;
    (void)av;
    while (ac)
{
    str = readline("\033[0;32m~ minishell\x1b[0m "); // TODO remove comments on this line
    // str = "arg1| arg2";
    add_history(str);
    toke = lexi(str);
    if (toke->type != 7 && toke->type != 6)
    {
        toke = ft_expand(toke);
        toke = rmv_quotes(toke);
        cmds = init_struct(toke);
    }
        
        // while (exp->next != NULL)
        // {
            // printf("expanded = %s\n", exp->expanded);
            // exp = exp->next;
        // }
        // printf("holaaaaaaa\n");
    // printf("%s\n", str);
}
}

// "$l.g"
// $USER
//"$PATH....$USER'$LLL',,,123$L$USER"
//ls >'>'<<'a'>'file'a|pwd>'<<'
//echo $a_
//export a_=bk
// separe bhadok l3aybat
//"$USER"'$T'$HOME
//''""''""RRRRR$RF
//echo $
//echo "$4USER"
//$HOME...$USER'$HOME'"$USER"$l
//$nnnn$nnnn$kk..$USE you ignore everything before something that doesnt expanded



//expand 127;
//li ba9i ma khedamch 
// //"$PATH....$USER'$LLL',,,123$L$USER"
//echo $
//echo hello world | echo "'$USER'"      kan 7ayed 7ta l quotes lwestaniyin



//herdoc = kat openi file katkteb fih o ay 7aja tketbat katcompara m3a delimitr bach ytcolsa l file
// ctrl d in herdoc 