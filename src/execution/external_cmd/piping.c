#include "../../../includes/minishell.h"

void	error_msg(char *str)
{
	perror(str);
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
		{
			// free_arr_b((void **)pip);
			return (NULL);
		}
		if (pipe(pip[i]) == -1)
		{
			// free_arr_b((void **)pip);
			error_msg("error 🥴");
		}
		i++;
	}
	pip[i] = NULL;
	return (pip);
}

void signaled(int status)
{
	int	is_sig;

	is_sig = 0;
	if(WTERMSIG(status) == SIGINT)
	{
		if(!is_sig)
		{
			write(1, "\n", 1); //print new line 
			is_sig = 1; // to dont print it few times 
		} 
		G_EXIT_STATUS = 130;
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		if(!is_sig)
		{
			printf("Quit \n");
			is_sig = 1;
		}
		G_EXIT_STATUS = 131;
	}
}

void	 waiting_childs(t_pids *process_ids)
{
	int	(i), (status);
	i = 0;
	signal(SIGINT, SIG_IGN); // ignore SIGINT while waiting -> that only the child is affected, and the parent shell doesn’t react
	signal(SIGQUIT, SIG_IGN);
	while (i < process_ids->nbr_childs)
	{
		waitpid(process_ids->pids[i], &status, 0);
		if(WIFEXITED(status)) // if the program exited , extract the real exit status 
			G_EXIT_STATUS = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			signaled(status);
		i++;
	}
}
