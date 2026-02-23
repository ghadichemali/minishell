NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
LIBFT = libft/libft.a
SRC =	src/main.c \
		src/lexer/lexer.c \
		src/lexer/lexer_scan.c \
		src/lexer/lexer_ops.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_word.c
OBJ = $(SRC:.c=.o)
READLINE = -lreadline -lhistory -lncurses

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re