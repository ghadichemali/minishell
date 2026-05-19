NAME		= minishell
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -I includes
LIBFT		= libft/libft.a
READLINE	= -lreadline -lhistory -lncurses

SRC		=	src/main.c \
			src/lexer/lexer.c \
			src/lexer/lexer_scan.c \
			src/lexer/lexer_ops.c \
			src/lexer/lexer_utils.c \
			src/lexer/lexer_word.c \
			src/lexer/token_print.c \
			src/parser/parser.c \
			src/parser/token_cursor.c \
			src/parser/node_utils.c \
			src/parser/redir_utils.c \
			src/parser/parse_cmd.c \
			src/parser/parse_subshell.c \
			src/parser/parse_pipeline.c \
			src/parser/free_AST.c \
			src/parser/print_AST.c

OBJ		= $(SRC:.c=.o)

TEST_SRC	=	src/parser/test_parser.c \
			src/lexer/lexer.c \
			src/lexer/lexer_scan.c \
			src/lexer/lexer_ops.c \
			src/lexer/lexer_utils.c \
			src/lexer/lexer_word.c \
			src/lexer/token_print.c \
			src/parser/parser.c \
			src/parser/token_cursor.c \
			src/parser/node_utils.c \
			src/parser/redir_utils.c \
			src/parser/parse_cmd.c \
			src/parser/parse_subshell.c \
			src/parser/parse_pipeline.c \
			src/parser/free_AST.c \
			src/parser/print_AST.c

TEST_OBJ	= $(TEST_SRC:.c=.o)
TEST_BIN	= test_parser

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

test: $(LIBFT) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIBFT) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(OBJ) $(TEST_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(TEST_BIN)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re test