#include "../minishell.h"

// int t_command(char* input, s_node **list, int start, int *commandFlag)
// {
// 	int i = start;
// 	Token* newToken;

// 	newToken = malloc(sizeof(Token));
// 	if (!newToken)
// 		return - 1;
// 	*commandFlag = 1;
// 	newToken->type = COMMAND;
// 	while (input[i] && isWhiteSpace(input[i]) != 1) {
// 		i++;
// 	}
// 	newToken->value = ft_substr(input, start, i - start);
// 	add_node(list, &newToken);
// 	return i - start;
// }

int t_quoted_argument(char *input, s_node** list, int start, int quoteType)
{
	Token* newToken;
	int i;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return -1;
	i = start + 1;
	while (input[i] && input[i] != quoteType)
		i++;
	if (input[i] != quoteType)
	{
		_unclosed_quotes_error();
		free(newToken);
		return -1;
	}
	newToken->value = ft_substr(input, start + 1, i - start - 1);
	newToken->type = WORD;
	add_node(list, &newToken);
	return i + 1 - start;
}

int t_argument(char* input, s_node** list, int start) 
{
	int i;
	Token* newToken;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	i = start;
	while (input[i] && !(isWhiteSpace(input[i]) == 1 || isSeparator(input[i]) == 1)) 
		i++;
	newToken->value = ft_substr(input, start, i - start);
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
	else if (ft_isalnum(oneAhead) == 1 || oneAhead == 34 || oneAhead == 39 
		|| isWhiteSpace(oneAhead) == 1 || oneAhead == '_' || oneAhead == '.')
	{
		if (current == '<')
			newToken->type = REDIR_IN;
		else
			newToken->type = REDIR_OUT;
		newToken->value = ft_substr(input, start, 1);
	} 
	else {
		_invalid_redirection_error();
		free(newToken);
		return -1;
	}
	add_node(list, &newToken);
	return ft_strlen(newToken->value);
}