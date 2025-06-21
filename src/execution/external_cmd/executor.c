#include "../../../includes/minishell.h"

int	len_list_cmd(t_cmd *temp)
{
	int i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return(i);
}

void ft_execve(t_env *envs, t_cmd *tmp_cmd)
{
	char *exec_path;
	char **env_arr;

	exec_path = executable_path(tmp_cmd->full_cmd[0], envs);
	env_arr = envs_to_array(envs);// no need to check NULL, because can run execve without envs
	if(execve(exec_path, tmp_cmd->full_cmd, env_arr) == -1)
	{
		ft_putstr_fd(tmp_cmd->full_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

int is_parent_builtin(char *command)
{
	if (!command)
        return (-1);
    
	if (ft_strcmp(command, "cd") == 0)
		return (0);
	if (ft_strcmp(command, "pwd") == 0)
		return (0);
	if (ft_strcmp(command, "export") == 0)
		return (0);
	if (ft_strcmp(command, "unset") == 0)
		return (0);
	if (ft_strcmp(command, "echo") == 0)
		return (0);
	if (ft_strcmp(command, "exit") == 0)
		return (0);
		
	return (-1);
}

t_pids *execute_commands(t_env **envs, t_cmd *tmp_cmd)
{
	int **pipes;
	int (i), (len_cmd);

	t_pids *process_ids;

	process_ids = malloc(sizeof(t_pids)); // allocate struct
	if(!process_ids)
		return(NULL);
	
	process_ids->pids = malloc(sizeof(int) * 1024); // allocate array of ids
	if(!process_ids->pids)
		return(NULL);

	// process_ids->nbr_childs len of linked list (how many command)
	len_cmd = len_list_cmd(tmp_cmd);

	// allocate 2d array of pipes
	pipes = piping(len_cmd - 1);
	if(!pipes)
		return(NULL);

	process_ids->nbr_childs = 0;
	i = 0;

	//exit status

	// if(ft_strcmp(tmp_cmd->full_cmd[0], "echo") == 0 && ft_strcmp(tmp_cmd->full_cmd[1], "?") == 0)
	// 	printf("my exit status = %d\n", G_EXIT_STATUS);
	// else { ////// test exit status


	while (i < len_cmd) // while to execute commands
	{
		if(len_cmd == 1) // if one command
		{
			duplication(i, len_cmd, pipes, tmp_cmd);
			// if(is_parent_builtin(tmp_cmd->full_cmd[0]) == 0) // without env , should run in child. 
			// 	ft_builtin(tmp_cmd->full_cmd, envs);
			if(ft_builtin(tmp_cmd->full_cmd, envs) == -1)  // is a builtin don't fork , execute it in parent.
			{
				process_ids->pids[process_ids->nbr_childs] = fork();
				if(process_ids->pids[process_ids->nbr_childs] == 0)
				{
					close_pipes(len_cmd - 1, pipes); // close pipes inherted from parent
					ft_execve((*envs), tmp_cmd);
				}
				process_ids->nbr_childs++; //the number of childes forked
			}
		}
		else //many commands 
		{
			process_ids->pids[process_ids->nbr_childs] = fork();
			if(process_ids->pids[process_ids->nbr_childs] == 0)
			{
				// duplicate and CLOSE , stdout stdin with pipes
				duplication(i, len_cmd, pipes, tmp_cmd);
				close_pipes(len_cmd - 1, pipes); // close pipes inherted from parent

				// execute the commands
				if (ft_builtin(tmp_cmd->full_cmd, envs) == 0)
					exit(0); // child must exit after finishing the builtin
				else
					ft_execve((*envs), tmp_cmd);
			}
			process_ids->nbr_childs++; //the number of childes forked
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}

// } ///// test exit status 

	close_pipes(len_cmd - 1, pipes);

	return(process_ids);
}

void	ft_perror(char *err_msg, int len_cmd, int **pipes)
{
	perror(err_msg);
	close_pipes(len_cmd - 1, pipes);
	exit(EXIT_FAILURE);
}

void duplication(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
{
	if(i == 0) // first command
	{
		if(tmp_cmd->in_file != -1) // duplicate stdin with pipes or redirection,
		{
			if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
			close(tmp_cmd->in_file);
		}
		if(tmp_cmd->out_file != -1)
		{
			if(dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
			close(tmp_cmd->out_file);
		}
		else if(len_cmd > 1) // that means we have pipes
		{
			if(dup2(pipes[i][1], STDOUT_FILENO) == -1) // diplucate the stdout to write in pipe
				ft_perror("dup2 ", len_cmd, pipes);
		}
	}

	else if (i < len_cmd - 1) // middle command [ .... | ..... | .... ]
	{
		if(tmp_cmd->in_file != -1) 
		{
			if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
			close(tmp_cmd->in_file);
		}
		else
		{
			if(dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
		}

		if(tmp_cmd->out_file != -1)
		{
			if(dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
			close(tmp_cmd->out_file);
		}
		else
		{
			if(dup2(pipes[i][1], STDOUT_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
		}
	}

	else if (i == len_cmd - 1)  // last command 
	{
		if(tmp_cmd->in_file != -1) 
		{
			if(dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
			close(tmp_cmd->in_file);
		}
		else
		{
			if(dup2(pipes[i - 1][0], STDIN_FILENO) == -1) // diplucate the stdin to read from pipe
				ft_perror("dup2 ", len_cmd, pipes);
		}

		if(tmp_cmd->out_file != -1)
		{
			if(dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
				ft_perror("dup2 ", len_cmd, pipes);
			close(tmp_cmd->out_file);
		}
	}
}
