/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:37:10 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:36:21 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	space_skip_main(char *rdl)
{
	int	len;

	if (skip_space_str(rdl) == 1)
	{
		len = ft_strlen(rdl);
		add_history(rdl);
	}
	else
	{
		len = 0;
		free(rdl);
		return (0);
	}
	return (len);
}

int	skip_space_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*shell_prompt(t_env *envs)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		prompt = ft_strjoin(cwd, " $> ", envs);
		free(cwd);
		return (prompt);
	}
	cwd = get_env_value("PWD", envs);
	if (!cwd)
	{
		cwd = ft_strdup("..", envs);
		prompt = ft_strjoin(cwd, " $> ", envs);
		return (prompt);
	}
	prompt = ft_strjoin(cwd, " $> ", envs);
	return (prompt);
}
