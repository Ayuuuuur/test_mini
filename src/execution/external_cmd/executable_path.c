/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:43:09 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:43:09 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_arr_b(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*get_path_env(t_env *envs)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, "PATH") == 0)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

char	*find_exec_file(char **dirc, char *cmd, t_env *envs)
{
	char	*pathname;
	int		i;

	i = 0;
	while (dirc[i])
	{
		pathname = build_path(dirc[i], cmd, envs);
		if (!pathname)
			return (NULL);
		if (access(pathname, X_OK) == 0)
			return (pathname);
		i++;
	}
	return (NULL);
}

char	*build_path(char *dirc, char *cmd, t_env *envs)
{
	char	*temp;
	char	*pathname;

	temp = ft_strjoin(dirc, "/", envs);
	if (!temp)
		return (NULL);
	pathname = ft_strjoin(temp, cmd, envs);
	return (pathname);
}

char	*executable_path(char *cmd, t_env *envs)
{
	char	**dirc;
	char	*pathname;
	char	*path;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (cmd[0] == '/' || cmd[0] == '.' )
		return (NULL);
	path = get_path_env(envs);
	dirc = ft_split(path, ':', envs);
	if (!dirc)
		return (NULL);
	pathname = find_exec_file(dirc, cmd, envs);
	if (!pathname)
		return (NULL);
	return (pathname);
}
