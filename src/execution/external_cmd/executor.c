#include "../../../includes/minishell.h"

void ft_execve(t_env *envs, t_cmd *tmp_cmd)
{ 
	char *exec_path;
	char **env_arr;

	exec_path = executable_path(tmp_cmd->full_cmd[0], envs);
	if(exec_path == NULL)
	{
		ft_putstr_fd(tmp_cmd->full_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_memory(&(envs->head_gc));
		free_list(&envs);
		exit(127);
	}
	env_arr = envs_to_array(envs);// no need to check NULL, because can run execve without envs
	if(execve(exec_path, tmp_cmd->full_cmd, env_arr) == -1)
	{
		ft_putstr_fd(tmp_cmd->full_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_memory(&(envs->head_gc));
		free_list(&envs);
		exit(127);
	}
}

void execute_one_command(t_pids **process_ids, t_cmd *tmp_cmd, int **pipes, t_env **envs)
{
	int len_cmd;

	len_cmd = len_list_cmd(tmp_cmd);
	if(ft_builtin(tmp_cmd->full_cmd,  0, envs) == -1)  // is a builtin don't fork , execute it in parent.
	{
		(*process_ids)->pids[(*process_ids)->nbr_childs] = fork();
		if((*process_ids)->pids[(*process_ids)->nbr_childs] == 0)
		{
			set_signals_dfl();
			close_pipes(len_cmd - 1, pipes); // close pipes inherted from parent
			ft_execve((*envs), tmp_cmd);
		}
		(*process_ids)->nbr_childs++; //the number of childes forked
	}
}

void execute_many_cmnd(t_cmd *tmp_cmd, t_env **envs, int **pipes, int len_cmd)
{
	close_pipes(len_cmd - 1, pipes); // close pipes inherted from parent
	if (ft_builtin(tmp_cmd->full_cmd, 1, envs) == 0)	// execute the commands
		exit(0); // child must exit after finishing the builtin
	else
		ft_execve((*envs), tmp_cmd);
}

void run_commands(t_pids **process_ids, t_cmd *tmp_cmd, int **pipes, t_env **envs)
{
	int (i), (len_cmd);
	i = 0;
	len_cmd = len_list_cmd(tmp_cmd); // process_ids->nbr_childs len of linked list (how many command)
	while (i < len_cmd) // while to execute commands
	{
		if(len_cmd == 1) // if one command
		{
			if(duplication(i, len_cmd, pipes, tmp_cmd) == 1)
				clean_memory(&((*envs)->head_gc));
			execute_one_command(process_ids, tmp_cmd, pipes, envs);
		}
		else //many commands 
		{
			(*process_ids)->pids[(*process_ids)->nbr_childs] = fork();
			if((*process_ids)->pids[(*process_ids)->nbr_childs] == 0)
			{
				set_signals_dfl();
				if(duplication(i, len_cmd, pipes, tmp_cmd) == 1)
					clean_memory(&((*envs)->head_gc));
				execute_many_cmnd(tmp_cmd, envs, pipes, len_cmd);
			}
			(*process_ids)->nbr_childs++; //the number of childes forked
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	} // add here exit status
}

t_pids *execute_commands(t_env **envs, t_cmd *tmp_cmd)
{
	int **pipes;
	t_pids *process_ids;
	int len_cmd;
	
	process_ids = g_collector(sizeof(t_pids), (*envs)); // allocate struct
	if(!process_ids)
		return(NULL);
	process_ids->pids = g_collector(sizeof(int) * 1024, (*envs)); // allocate array of ids
	if(!process_ids->pids)
		return(NULL);
	len_cmd = len_list_cmd(tmp_cmd); // process_ids->nbr_childs len of linked list (how many command)
	pipes = piping(len_cmd - 1, (*envs)); // allocate 2d array of pipes
	if(!pipes)
		return(NULL);
	process_ids->nbr_childs = 0;
	run_commands(&process_ids, tmp_cmd, pipes, envs);
	close_pipes(len_cmd - 1, pipes);
	return(process_ids);
}

// //exit status

// if(ft_strcmp(tmp_cmd->full_cmd[0], "echo") == 0 && ft_strcmp(tmp_cmd->full_cmd[1], "?") == 0)
// 	printf("my exit status = %d\n", g_exit_status);
// else { ////// test exit status

// } ///// test exit status
