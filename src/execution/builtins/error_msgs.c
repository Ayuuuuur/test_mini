#include "../../../includes/minishell.h"

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	g_exit_status = 1;
	return(EXIT_FAILURE); // exit status == 1
}

int ft_perror_cd()
{
	g_exit_status = 1;
	perror("minishell");
	return(EXIT_FAILURE);	
}


int	ft_perror(char *err_msg, int len_cmd, int **pipes)
{
	perror(err_msg);
	close_pipes(len_cmd - 1, pipes);
	g_exit_status = 1;
	return(g_exit_status);
	// exit(EXIT_FAILURE);
}
