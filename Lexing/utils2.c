#include "../minishell.h"

char* add_quoted_part(char* input, int* i)
{
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

int add_to_buffer(char* input, char** buffer, int* i)
{
	int buf_i;
	int part_len;
	char* part;

	buf_i = 0;
	while (input[*i] && !(isWhiteSpace(input[*i]) == 1 || isSeparator(input[*i]) == 1))
	{
		if (input[*i] == 34 || input[*i] == 39)
		{
			part = add_quoted_part(input, i);
			if (!part)
				return 0;
			part_len = ft_strlen(part);
			ft_memcpy(*buffer + buf_i, part, part_len);
			buf_i += part_len;
			free(part);
		}
		else
			(*buffer)[buf_i++] = input[(*i)++];
	}
	return 1;
}

void set_redir_token_values(char* input, Token** token, int start)
{
	char current;
	char oneAhead;

	current = input[start];
	oneAhead = input[start + 1];
	if (current == oneAhead) {
		if (current == '<')
			(*token)->type = HEREDOC;
		else
			(*token)->type = REDIR_APPEND;
		(*token)->value = ft_substr(input, start, 2);
	}
	else 
	{
		if (current == '<')
			(*token)->type = REDIR_IN;
		else
			(*token)->type = REDIR_OUT;
		(*token)->value = ft_substr(input, start, 1);
	}
}