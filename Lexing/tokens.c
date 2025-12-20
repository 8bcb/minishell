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
	char* tmpArg;
	char* newArg;
	char* newPart;

	newToken = malloc(sizeof(Token));
	if (!newToken)
		return - 1;
	i = start;
	newArg = ft_strdup("");
	while (input[i] && !(isWhiteSpace(input[i]) == 1 || isSeparator(input[i]) == 1))
	{
		tmpArg = newArg;
		if (input[i] == 34 || input[i] == 39)
		{
			newPart = add_quoted_part(input, &i);
			if (!newPart)
			{
				free(newArg);
				free(newToken);
				return _unclosed_quotes_error;
			}
			newArg = ft_strjoin(tmpArg, newPart);
		}
		else
		{
			newPart = ft_substr(input, i, 1);
			newArg = ft_strjoin(tmpArg, newPart);
			i++;
		}
		free(tmpArg);
		free(newPart);
	}
	newToken->value = newArg;
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