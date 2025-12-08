NAME := mini
SRC := main.c \
Lexing/lexer.c \
Lexing/utils.c \
Lexing/linked_list.c \
Lexing/tokens.c \
Lexing/errors.c \
Parsing/parsing.c \
Parsing/parsing_errors.c \
Parsing/parsing_utils.c \
execution/exec_ast.c \
execution/exec_command.c \
execution/exec_pipeline.c \
execution/exec_external/exec_external.c \
execution/exec_external/exec_external_utils.c \
execution/builtins/echo.c \
execution/builtins/exec_builtin.c \
execution/redirection/exec_redirection.c 
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS := -Wall -Wextra -Werror
LDLIBS := -lreadline -lft
INCLUDES := -I . -I libft

LIBFT_DIR	:= libft
LIBFT_A		:= $(LIBFT_DIR)/libft.a

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) $(LDLIBS) -o $@

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all