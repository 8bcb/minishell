#include "../minishell.h"

int t_word(char* input, s_node** list, int start) 
{
	int i;
	int success;
	Token* newToken;
	char* buffer;

	newToken = malloc(sizeof(Token));
	buffer = calloc(ft_strlen(&(input[start])) + 1, sizeof(char));
	if (!newToken || !buffer)
		return - 1;
	i = start;
	success = add_to_buffer(input, &buffer, &i);
	if (!success)
	{
		free(buffer);
		free(newToken);
		return _unclosed_quotes_error();
	}
	newToken->value = buffer;
	newToken->type = WORD;
	add_node(list, &newToken);
	return i - start;
}

int t_pipe(s_node **list)
int t_pipe(s_node **list)
{
	Token* newToken;
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	newToken->type = PIPE;
	newToken->value = ft_strdup("|");
	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	newToken->type = PIPE;
	newToken->value = ft_strdup("|");
	add_node(list, &newToken);
	return 1;
}

int t_redirection(char *input, s_node **list, int start) 
int t_redirection(char *input, s_node **list, int start) 
{
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	set_redir_token_values(input, &newToken, start);
	if (!newToken->value) {
		free(newToken);
		return _invalid_redirection_error();
	}
	add_node(list, &newToken);
	return ft_strlen(newToken->value);
	return ft_strlen(newToken->value);
}