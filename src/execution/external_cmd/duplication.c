#include "../../../includes/minishell.h"

int dup_first_cmnd(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
{
	if(tmp_cmd->in_file != -1) // duplicate stdin with pipes or redirection,
	{
		if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->in_file);
	}
	if(tmp_cmd->out_file != -1)
	{
		if(dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->out_file);
	}
	else if(len_cmd > 1) // that means we have pipes
	{
		if(dup2(pipes[i][1], STDOUT_FILENO) == -1) // diplucate the stdout to write in pipe
			return(ft_perror("dup2 ", len_cmd, pipes));
	}
	return(0);
}

int dup_middle_cmnds(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
{
	if(tmp_cmd->in_file != -1) 
	{
		if (dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->in_file);
	}
	else
	{
		if(dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
	}
	if(tmp_cmd->out_file != -1)
	{
		if(dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->out_file);
	}
	else
	{
		if(dup2(pipes[i][1], STDOUT_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
	}
	return(0);
}

int dup_last_cmnd(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
{
	if(tmp_cmd->in_file != -1) 
	{
		if(dup2(tmp_cmd->in_file, STDIN_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->in_file);
	}
	else
	{
		if(dup2(pipes[i - 1][0], STDIN_FILENO) == -1) // diplucate the stdin to read from pipe
			return(ft_perror("dup2 ", len_cmd, pipes));
	}
	if(tmp_cmd->out_file != -1)
	{
		if(dup2(tmp_cmd->out_file, STDOUT_FILENO) == -1)
			return(ft_perror("dup2 ", len_cmd, pipes));
		close(tmp_cmd->out_file);
	}
	return(0);
}

int duplication(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd) // fail = 1, succes = 0;
{
	if(i == 0)
		return(dup_first_cmnd(i, len_cmd, pipes, tmp_cmd));
	else if (i < len_cmd - 1)
		return(dup_middle_cmnds(i, len_cmd, pipes, tmp_cmd));
	else if (i == len_cmd - 1)
		return(dup_last_cmnd(i, len_cmd, pipes, tmp_cmd));
	return(0);
}
