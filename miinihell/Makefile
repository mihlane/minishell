# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhabibi- <mhabibi-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 17:12:13 by rarahhal          #+#    #+#              #
#    Updated: 2023/01/15 12:48:18 by mhabibi-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS =	execution.c \
		env.c \
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
		execution/execut_libft/ft_itoa.c \
		execution/execut_libft/ft_substr.c \
		read.c\
		lexer.c\
		expand.c\
		lexi_toke.c\
		get_next_line.c\
		get_next_line_utils.c\
		expand_herdoc.c ft_strncmp.c

# READLINE = ~/.brew/opt/readline
OSRC = $(SRCS:.c=.o)
OLIBFT = $(LIBFT:.c=.o)
OEXLIBFT = $(EXECUT_LIBFT:.c=.o)

$(NAME):  $(OSRC) $(OLIBFT) $(OEXLIBFT)
	@$(CC) $(CFLAGS) -lreadline $(OSRC) $(OLIBFT) $(OEXLIBFT) -o $(NAME)  #-fsanitize=address -g3

%.o: %.c
	@$(CC) $(CFLAGS) -lreadline -Qunused-arguments -o $@ -c $<
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