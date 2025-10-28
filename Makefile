NAME := minishell
SRC := main.c \
Lexing/lexer.c \
execution/exec_ast.c execution/exec.h \
utils/ft_strcmp.c \
builtins/echo.c

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I . -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all