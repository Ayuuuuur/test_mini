#include "../../../includes/minishell.h"

void	error_msg(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	null_error(char *str)
{
	write(2, "error :", 8);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}


void	close_pipes(int nbr_pipes, int **ends)
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if(close(ends[i][0]) != 0 )
			perror("close ");
		if(close(ends[i][1]) != 0)
			perror("close ");
		i++;
	}
}

void	 waiting_childs(t_pids *process_ids)
{
	int	i;
	int status;

	i = 0;
	while (i < process_ids->nbr_childs)
	{
		waitpid(process_ids->pids[i], &status, 0);
		if(WIFEXITED(status)) // if the program exited , extract the real exit status 
			G_EXIT_STATUS = WEXITSTATUS(status);
		
		// printf("waitpid -> %d /\\ exit status -> %d\n", process_ids->pids[i], G_EXIT_STATUS);
		i++;
	}
}

int	**piping(int lines)
{
	int	**pip;
	int	i;

	i = 0;
	pip = (int **)malloc((lines + 1) * sizeof(int *));
	if (!pip)
		return (NULL);
	while (i < lines)
	{
		pip[i] = (int *)malloc(2 * sizeof(int));
		if (!pip[i])
		{
			free_arr_b((void **)pip);
			return (NULL);
		}
		if (pipe(pip[i]) == -1)
		{
			free_arr_b((void **)pip);
			error_msg("error 🥴8");
		}
		i++;
	}
	pip[i] = NULL;
	return (pip);
}
