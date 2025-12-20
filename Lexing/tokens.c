#include "../minishell.h"

char* add_quoted_part(char* input, int* i) {
	int iter;
	int quote;
	int start;

	start = *i + 1;
	iter = *i;
	quote = input[iter];
	iter++;
	while (input[iter] && input[iter] != quote)
		iter++;
	if (input[iter] != quote)
		return NULL;
	*i = iter + 1;
	return ft_substr(input, start, iter - start);
}

int t_argument(char* input, s_node** list, int start) 
{
	int i;
	Token* newToken;
	char* buffer;
	char* part;
	int buf_i;

	newToken = malloc(sizeof(Token));
	buffer = calloc(ft_strlen(&(input[start])) + 1, sizeof(char));
	if (!newToken || !buffer)
		return - 1;
	buf_i = 0;
	i = start;
	while (input[i] && !(isWhiteSpace(input[i]) == 1 || isSeparator(input[i]) == 1))
	{
		if (input[i] == 34 || input[i] == 39)
		{
			part = add_quoted_part(input, &i);
			if (!part)
			{
				free(buffer);
				free(newToken);
				return _unclosed_quotes_error();
			}
			ft_memcpy(buffer + buf_i, part, ft_strlen(part));
			buf_i += ft_strlen(part);
			free(part);
		}
		else
			buffer[buf_i++] = input[i++];
	}
	newToken->value = buffer;
	newToken->type = WORD;
	add_node(list, &newToken);
	return i - start;
}

int t_pipe(s_node **list)
{
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	newToken->type = PIPE;
	newToken->value = ft_strdup("|");
	add_node(list, &newToken);
	return 1;
}

int t_redirection(char *input, s_node **list, int start) 
{
	Token* newToken;
	char current;
	char oneAhead;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	current = input[start];
	oneAhead = input[start + 1];
	if (current == oneAhead) {
		if (current == '<')
			newToken->type = HEREDOC;
		else
			newToken->type = REDIR_APPEND;
		newToken->value = ft_substr(input, start, 2);
	}
	else 
	{
		if (current == '<')
			newToken->type = REDIR_IN;
		else
			newToken->type = REDIR_OUT;
		newToken->value = ft_substr(input, start, 1);
	} 
	if (!newToken->value) {
		free(newToken);
		return _invalid_redirection_error();
	}
	add_node(list, &newToken);
	return ft_strlen(newToken->value);
}