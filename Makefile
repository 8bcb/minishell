NAME        := mini

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
INCLUDES    := -I . -I libft
LDLIBS      := -lft -lreadline

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRCS        := \
	main.c \
	Lexing/utils.c \
	Lexing/lexer.c \
	Lexing/linked_list.c \
	Lexing/tokens.c \
	Lexing/errors.c \
	Parsing/parsing.c \
	Parsing/parsing_errors.c \
	Parsing/parsing_utils.c \
	execution/exec_ast.c \
	execution/exec_command.c \
	execution/exec_pipeline.c \
	execution/exec_pipeline_utils.c \
	execution/exec_pipeline_utils_2.c \
	execution/exec_utils.c \
	execution/exec_external/exec_external.c \
	execution/exec_external/exec_external_utils.c \
	execution/builtins/echo.c \
	execution/builtins/exec_builtin.c \
	execution/builtins/cd.c \
	execution/builtins/env.c \
	execution/builtins/exit.c \
	execution/builtins/export.c \
	execution/builtins/pwd.c \
	execution/builtins/unset.c \
	execution/redirection/exec_redirection.c \
	execution/redirection/exec_redirection_utils.c \
	env_utils.c \
	signals.c \
	execution/exec_free_ast.c \

OBJS        := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LDLIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
