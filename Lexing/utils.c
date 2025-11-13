#include "../minishell.h"

int isWhiteSpace(char c) 
{
	if ((c >= 9 && c <= 13) || c == 32)
		return 1;
	return 0;
}

int isAlphanumeric(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == 95 || (c >= 48 && c <= 57))
		return 1;
	else
		return 0;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*dst;

	res = (char *)malloc(len);
	if (res == NULL)
		return (NULL);
	dst = res;
	while (len - 1)
	{
		*dst = s[start];
		dst++;
		start++;
		len--;
	}
	*dst = '\0';
	return (res);
}

char	*strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*str;
	size_t	t_len;

	t_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)malloc(t_len * sizeof(int));
	if (res == NULL)
		return (NULL);
	str = res;
	while (*s1)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2)
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (res);
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
