/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:12:34 by hind              #+#    #+#             */
/*   Updated: 2025/07/04 00:12:34 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error_msg(char *str, t_env *envs)
{
	perror(str);
	clean_memory(&(envs->head_gc));
	exit(EXIT_FAILURE);
}

void	close_pipes(int nbr_pipes, int **ends)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (close(ends[i][0]) != 0)
			perror("close ");
		if (close(ends[i][1]) != 0)
			perror("close ");
		i++;
	}
}

int	**piping(int lines, t_env *envs)
{
	int	**pip;
	int	i;

	i = 0;
	pip = (int **)g_collector((lines + 1) * sizeof(int *), envs);
	if (!pip)
		return (NULL);
	while (i < lines)
	{
		pip[i] = (int *)g_collector(2 * sizeof(int), envs);
		if (!pip[i])
			return (NULL);
		if (pipe(pip[i]) == -1)
			error_msg("error 🥴", envs);
		i++;
	}
	pip[i] = NULL;
	return (pip);
}

void	signaled(int status)
{
	int	is_sig;

	is_sig = 0;
	if (WTERMSIG(status) == SIGINT)
	{
		if (!is_sig)
		{
			write(1, "\n", 1);
			is_sig = 1;
		}
		g_exit_status = 130;
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		if (!is_sig)
		{
			printf("Quit \n");
			is_sig = 1;
		}
		g_exit_status = 131;
	}
}

void	waiting_childs(t_pids *process_ids)
{
	int (i), (status);
	status = 0;
	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < process_ids->nbr_childs)
	{
		waitpid(process_ids->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			signaled(status);
		i++;
	}
}
