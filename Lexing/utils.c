#include "../minishell.h"

int isWhiteSpace(char c) 
{
	if ((c >= 9 && c <= 13) || c == 32)
		return 1;
	return 0;
}

char* trim(char *input)
{
	int len;
	int i;
	int j;
	int iter;

	i = 0;
	len = ft_strlen(input);
	while (i < len && input[i] == ' ')
		i++;
	j = 0;
	iter = len - 1;
	while (iter >= 0 && input[iter] == ' ')
	{
		j++;
		iter--;
	}
	return ft_substr(input, i, len - i - j + 1);
}
