/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:31:12 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:41:12 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	dup_first_cmnd(int i, int len_cmd, int **pipes, t_cmd *tmp_cmd)
{
	if (tmp_cmd->in_file != -1)
	{
		if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->in_file);
	}
	if (tmp_cmd->out_file != -1)
	{
		if (dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->out_file);
	}
	else if (len_cmd > 1)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
	}
	return (0);
}

int	dup_middle_cmnds(int i, int len_cmd, int **pipes, t_cmd *tmp_cmd)
{
	if (tmp_cmd->in_file != -1)
	{
		if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->in_file);
	}
	else
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
	}
	if (tmp_cmd->out_file != -1)
	{
		if (dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->out_file);
	}
	else
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
	}
	return (0);
}

int	dup_last_cmnd(int i, int len_cmd, int **pipes, t_cmd *tmp_cmd)
{
	if (tmp_cmd->in_file != -1)
	{
		if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->in_file);
	}
	else
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
	}
	if (tmp_cmd->out_file != -1)
	{
		if (dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
			return (ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->out_file);
	}
	return (0);
}

int	duplication(int i, int len_cmd, int **pipes, t_cmd *tmp_cmd)
{
	if (i == 0)
		return (dup_first_cmnd(i, len_cmd, pipes, tmp_cmd));
	else if (i < len_cmd - 1)
		return (dup_middle_cmnds(i, len_cmd, pipes, tmp_cmd));
	else if (i == len_cmd - 1)
		return (dup_last_cmnd(i, len_cmd, pipes, tmp_cmd));
	return (0);
}
