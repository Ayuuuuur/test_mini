/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:36:15 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/03 22:37:24 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*save_in_out(t_env *envs)
{
	int	*arr_in_out;

	arr_in_out = saved_stdin_out(envs);
	if (arr_in_out[0] == -1 || arr_in_out[1] == -1)
	{
		free_list(&envs);
		exit(g_exit_status);
	}
	return (arr_in_out);
}

int	*saved_stdin_out(t_env *envs)
{
	int	*in_out;

	in_out = (int *)g_collector(sizeof(int) * 2, envs);
	in_out[0] = dup(STDIN_FILENO);
	in_out[1] = dup(STDOUT_FILENO);
	if (in_out[0] == -1 || in_out[1] == -1)
		perror("minishell");
	return (in_out);
}

void	restore_stdin_out(int *saved_in_out)
{
	if (dup2(saved_in_out[0], STDIN_FILENO) == -1)
		perror("dup2 ");
	if (dup2(saved_in_out[1], STDOUT_FILENO) == -1)
		perror("dup2 ");
	close(saved_in_out[0]);
	close(saved_in_out[1]);
}
