#include "../../../includes/minishell.h"


int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	G_EXIT_STATUS = 1;
	return(EXIT_FAILURE); // exit status == 1
}

int ft_perror_cd()
{
	G_EXIT_STATUS = 1;
	perror("minishell");
	return(EXIT_FAILURE);	
}


void	ft_perror(char *err_msg, int len_cmd, int **pipes)
{
	perror(err_msg);
	close_pipes(len_cmd - 1, pipes);
	G_EXIT_STATUS = 1;
	exit(EXIT_FAILURE);
}
