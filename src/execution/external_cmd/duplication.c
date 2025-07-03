#include "../../../includes/minishell.h"

void dup_first_cmnd(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
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

void dup_middle_cmnds(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
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

void dup_last_cmnd(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
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


void duplication(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd)
{
	if(i == 0)
		dup_first_cmnd(i, len_cmd, pipes, tmp_cmd);
	else if (i < len_cmd - 1)
		dup_middle_cmnds(i, len_cmd, pipes, tmp_cmd);
	else if (i == len_cmd - 1)
		dup_last_cmnd(i, len_cmd, pipes, tmp_cmd);		
}
