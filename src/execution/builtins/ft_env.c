/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:55:20 by hind              #+#    #+#             */
/*   Updated: 2025/07/04 03:03:00 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_perror_env(char *str, int exit_stat)
{
	ft_putstr_fd(str, 2);
	g_exit_status = exit_stat;
	return (g_exit_status);
}

int	ft_env(char **args, t_env *envs)
{
	if (!envs || !get_env_value("PATH", envs))
		return (ft_perror_env("minishell: env: \
			No such file or directory\n", 127));
	if (!executable_path("env", envs))
		return (ft_perror_env("env: command not found\n", 127));
	if (args[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (g_exit_status = 127);
	}
	while (envs)
	{
		if (envs->flag_exported == 1)
		{
			printf("%s", envs->key);
			printf("=");
			printf("%s\n", envs->value);
		}
		envs = envs->next;
	}
	return (g_exit_status = 0);
}
