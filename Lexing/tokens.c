#include "../minishell.h"

int t_command(char* input, s_node **list, int start, int *commandFlag)
{
	int i = start;
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	*commandFlag = 1;
	newToken->type = COMMAND;
	while (input[i] && isWhiteSpace(input[i]) != 1) {
		i++;
	}
	newToken->value = ft_substr(input, start, i - start);
	add_node(list, &newToken);
	return i - start;
}

int t_argument(char* input, s_node** list, int start) 
{
	int i;
	Token* newToken;
	int openQuote;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	i = start;
	openQuote = 0;
	if (input[i] == 34 || input[i] == 39) {
		openQuote = input[i];
		i++;
	}
	while (input[i] && ((openQuote == 0 && isWhiteSpace(input[i]) != 1) 
		|| (openQuote != 0 && input[i] != openQuote))) 
		i++;
	if (openQuote != 0 && input[i] == openQuote) {
		openQuote = 0;
		i++;
	}
	if (openQuote != 0) {
		_unclosed_quotes_error();
		return -1;
	}
	newToken->value = ft_substr(input, start, i - start);
	newToken->type = ARGUMENT;
	add_node(list, &newToken);
	return i - start;
}

int t_pipe(s_node **list, int *commandFlag)
{
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	*commandFlag = 0;
	newToken->type = PIPE;
	newToken->value = "|";
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
		else if (isWhiteSpace(oneAhead) == 1)
		{
			if (current == '<')
				newToken->type = REDIR_IN;
			else
				newToken->type = REDIR_OUT;
			newToken->value = ft_substr(input, start, 1);
		} 
		else
			_invalid_redirection_error();
	add_node(list, &newToken);
	return ft_strlen(newToken->value);
}