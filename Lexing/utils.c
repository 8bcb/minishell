#include "../minishell.h"

int isWhiteSpace(char c) 
{
	if ((c >= 9 && c <= 13) || c == 32)
		return 1;
	return 0;
}

int isSeparator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return 1;
	return 0;
}

int valid_first_sign(char c)
{
	if (ft_isalpha(c) || c == '<' || c == '>')
		return 1;
	return 0;
}

char* trim(char *input)
{
	int len;
	int start;
	int j;
	int iter;

	start = 0;
	len = ft_strlen(input);
	while (input[start] && isWhiteSpace(input[start]) == 1)
		start++;
	j = 0;
	iter = len - 1;
	while (input[iter] && isWhiteSpace(input[iter]) == 1)
	{
		j++;
		iter--;
	}
	return ft_substr(input, start, len - start - j);
}
