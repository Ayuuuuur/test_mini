/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:44:10 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:44:10 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_execve(t_env *envs, t_cmd *tmp_cmd)
{
	char	*exec_path;
	char	**env_arr;

	exec_path = executable_path(tmp_cmd->full_cmd[0], envs);
	if (exec_path == NULL)
	{
		ft_putstr_fd(tmp_cmd->full_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_memory(&(envs->head_gc));
		free_list(&envs);
		exit(127);
	}
	env_arr = envs_to_array(envs);
	if (execve(exec_path, tmp_cmd->full_cmd, env_arr) == -1)
	{
		ft_putstr_fd(tmp_cmd->full_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_memory(&(envs->head_gc));
		free_list(&envs);
		exit(127);
	}
}

void	exec_one_cmd(t_pids **pcss_ids, t_cmd *tm_cmd, int **pipes, t_env **env)
{
	int	len_cmd;

	len_cmd = len_list_cmd(tm_cmd);
	if (ft_builtin(tm_cmd->full_cmd, 0, env) == -1)
	{
		(*pcss_ids)->pids[(*pcss_ids)->nbr_childs] = fork();
		if ((*pcss_ids)->pids[(*pcss_ids)->nbr_childs] == 0)
		{
			set_signals_dfl();
			close_pipes(len_cmd - 1, pipes);
			ft_execve((*env), tm_cmd);
		}
		(*pcss_ids)->nbr_childs++;
	}
}

void	exec_many_cmnd(t_cmd *tmp_cmd, t_env **envs, int **pipes, int len_cmd)
{
	close_pipes(len_cmd - 1, pipes);
	if (ft_builtin(tmp_cmd->full_cmd, 1, envs) == 0)
		exit(0);
	else
		ft_execve((*envs), tmp_cmd);
}

void	run_commands(t_pids **pcss_ids, t_cmd *tm_cmd, int **pipes, t_env **env)
{
	int (i), (len_cmd);
	i = 0;
	len_cmd = len_list_cmd(tm_cmd);
	if (len_cmd == 1)
	{
		if (duplication(i, len_cmd, pipes, tm_cmd) == 1)
			clean_memory(&((*env)->head_gc));
		exec_one_cmd(pcss_ids, tm_cmd, pipes, env);
		(*pcss_ids)->nbr_childs++ ;
		return ;
	}
	while (i < len_cmd)
	{
		(*pcss_ids)->pids[(*pcss_ids)->nbr_childs] = fork();
		if ((*pcss_ids)->pids[(*pcss_ids)->nbr_childs] == 0)
		{
			set_signals_dfl();
			if (duplication(i, len_cmd, pipes, tm_cmd) == 1)
				clean_memory(&((*env)->head_gc));
			exec_many_cmnd(tm_cmd, env, pipes, len_cmd);
		}
		(*pcss_ids)->nbr_childs++ ;
		tm_cmd = tm_cmd->next;
		i++;
	}
}

t_pids	*execute_commands(t_env **envs, t_cmd *tmp_cmd)
{
	t_pids	*process_ids;
	int		**pipes;
	int		len_cmd;

	process_ids = g_collector(sizeof(t_pids), (*envs));
	if (!process_ids)
		return (NULL);
	process_ids->pids = g_collector(sizeof(int) * 1024, (*envs));
	if (!process_ids->pids)
		return (NULL);
	len_cmd = len_list_cmd(tmp_cmd);
	pipes = piping(len_cmd - 1, (*envs));
	if (!pipes)
		return (NULL);
	process_ids->nbr_childs = 0;
	run_commands(&process_ids, tmp_cmd, pipes, envs);
	close_pipes(len_cmd - 1, pipes);
	return (process_ids);
}
