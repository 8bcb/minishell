/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 08:33:09 by asia              #+#    #+#             */
/*   Updated: 2026/01/17 17:03:09 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	free_split(char **split_array)
{
	int	i;

	if (!split_array)
		return ;
	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

static const char	*get_base_dir(const char *dir)
{
	if (!dir || !*dir)
		return (".");
	return (dir);
}

static int	needs_slash(const char *base, size_t base_len)
{
	if (base_len > 0 && base[base_len - 1] != '/')
		return (1);
	return (0);
}

char	*join_path(const char *dir, const char *command)
{
	const char	*base;
	int			need_slash;
	size_t		base_len;
	size_t		command_len;
	char		*final_path;

	base = get_base_dir(dir);
	base_len = ft_strlen(base);
	command_len = ft_strlen(command);
	need_slash = needs_slash(base, base_len);
	final_path = malloc(base_len + command_len + need_slash + 1);
	if (!final_path)
		return (NULL);
	ft_memcpy(final_path, base, base_len);
	if (need_slash == 1)
		final_path[base_len] = '/';
	ft_memcpy(final_path + base_len + need_slash, command, command_len);
	final_path[base_len + command_len + need_slash] = '\0';
	return (final_path);
}

int	status_from_wait(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}
