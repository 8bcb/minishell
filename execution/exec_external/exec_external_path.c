/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziola <jziola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:03:55 by asia              #+#    #+#             */
/*   Updated: 2026/01/24 17:23:56 by jziola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"
#include "./exec_external.h"
#include <unistd.h>
#include "../env_utils/env_utils.h"

static char	*check_candidate(char *candidate, char **potential_paths)
{
	if (!candidate)
	{
		free_split(potential_paths);
		return (NULL);
	}
	if (access(candidate, X_OK) == 0)
	{
		free_split(potential_paths);
		return (candidate);
	}
	free(candidate);
	return (NULL);
}

char	*resolve_in_path(char *command, t_env *env)
{
	char	*path;
	char		**potential_paths;
	int			i;
	char		*candidate;

	path = search_env_list(env, "PATH", 4);
	if (!path || !*path)
		return (NULL);
	potential_paths = ft_split(path, ':');
	if (!potential_paths)
		return (NULL);
	i = 0;
	while (potential_paths[i])
	{
		candidate = join_path(potential_paths[i], command);
		candidate = check_candidate(candidate, potential_paths);
		if (candidate)
			return (candidate);
		i++;
	}
	free_split(potential_paths);
	free(path);
	return (NULL);
}
