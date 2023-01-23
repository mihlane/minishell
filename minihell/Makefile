# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 17:12:13 by lsemlali          #+#    #+#              #
#    Updated: 2023/01/20 19:45:30 by mhabibi-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra -g
CC = cc

SRCS =	execution.c \
		signals.c \
		execution/tools/tools1.c \
        execution/tools/arr_tools.c \
        execution/tools/arr_tools2.c \
		execution/ex_main_tools.c \
        execution/execute.c \
		execution/execute_1.c \
        execution/execute_2.c \
        execution/ex_tools.c \
        execution/ex_tools2.c \
        execution/builtins/cd.c \
        execution/builtins/cd_tools.c \
        execution/builtins/echo.c \
        execution/builtins/env.c \
        execution/builtins/exit.c \
        execution/builtins/export.c \
        execution/builtins/pwd.c \
        execution/builtins/unset.c \
        execution/builtins/builtins_tools.c \

EXECUT_LIBFT = execution/execut_libft/ft_split.c \
		execution/execut_libft/ft_atoi.c \
		execution/execut_libft/ft_strlen.c \
		execution/execut_libft/ft_strdup.c \
		execution/execut_libft/ft_strjoin.c \
		execution/execut_libft/ft_strcmp.c \
		execution/execut_libft/ft_strncmp.c \
		execution/execut_libft/ft_strchr.c \
		execution/execut_libft/ft_strlcpy.c \
		execution/execut_libft/ft_isalpha.c \
		execution/execut_libft/ft_tolower.c \
		execution/execut_libft/ft_lower.c \
		execution/execut_libft/ft_isdigit.c \
		execution/execut_libft/ft_putstr_fd.c \
		execution/execut_libft/ft_substr.c \
		parse/read.c\
		parse/read2.c\
		parse/read3.c\
		parse/read4.c\
		parse/read5.c\
		parse/read6.c\
		parse/main.c\
		parse/ft_itoa.c \
		parse/lexer.c\
		parse/lexer1.c\
		parse/lexer2.c\
		parse/lexer3.c\
		parse/expand.c\
		parse/expand1.c\
		parse/expand2.c\
		parse/expand3.c\
		parse/lexi_toke.c\
		parse/expand_herdoc.c\
		parse/expand_herdoc2.c\
		parse/expand_herdoc3.c\
		parse/ft_strncmp.c\
		parse/alloc.c \
		parse/env.c \
		parse/ft_calloc.c\
		parse/ft_strjoi.c\
		parse/ft_strdup_p.c\
		parse/laaast_moment.c\

READLINE = /Users/mhabibi-/goinfre/homebrew/opt/readline
OSRC = $(SRCS:.c=.o)
OLIBFT = $(LIBFT:.c=.o)
OEXLIBFT = $(EXECUT_LIBFT:.c=.o)

$(NAME):  $(OSRC) $(OLIBFT) $(OEXLIBFT)
	@$(CC) $(CFLAGS) -lreadline -L $(READLINE)/lib -I $(READLINE)/include $(OSRC) $(OLIBFT) $(OEXLIBFT) -o $(NAME)  #-fsanitize=address -g

%.o: %.c
	@$(CC) $(CFLAGS) -lreadline -L $(READLINE)/lib -I $(READLINE)/include -Qunused-arguments -o $@ -c $<
	@echo "\033[0;34mcompiling ...\033[0m"

all: $(NAME)

clean:
	@rm -f $(OSRC) $(OLIBFT) $(OEXLIBFT)
fclean: clean
	@rm -f $(NAME)
	@rm -f /tmp/_????????

re: fclean
	@make all

.PHONY: all clean fclean re

# ls > .
# ls > ""
#ls << a > '' | pwd
# syntax error  $?

# exit minishell with exit code