NAME = minishell
CC = cc
CFLAGS = -Werror -Wextra -Wall -g #-fsanitize=address 

SRC := 	$(wildcard src/parsing/*.c) \
		$(wildcard src/parsing/redirect_out/*.c) \
		$(wildcard src/parsing/heredoc/*.c) \
		$(wildcard src/parsing/expand/*.c) \
		$(wildcard src/execution/*.c) \
	 	$(wildcard src/execution/builtins/*.c) \
	 	$(wildcard src/execution/envp/*.c) \
	 	$(wildcard src/execution/signals/*.c) \
	 	$(wildcard src/execution/external_cmd/*.c) \
		$(wildcard *.c) \
		$(wildcard libft/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS)  $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
