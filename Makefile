NAME  = Minishell

SRCS  = read.c\
		lexer.c

CC = @cc

FLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address

all : $(NAME)
$(NAME) : $(SRCS) 
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "Minishell is ready"

clean :
	@rm -f $(NAME)

fclean : clean

re : fclean all
