#include "../../../includes/minishell.h"

int is_valid_exit(char *arg)
{
	int i;

	i = 0;
	if(arg[i] == '-' || arg[i] == '+')
		i++;
	if(!arg[i]) // in case we have just + or -
		return(-1);
	while (arg[i])
	{
		if((arg[i] < '0' || arg[i] > '9'))
			return(-1);
		i++;
	}
	return(0);
}


void ft_exit(char **args)
{
	int i;

	i = 0;
	while (args[i]) //count args
		i++;
	if(i == 1) // if just exit
	{
		ft_putstr_fd("exit\n", 2);
		exit(G_EXIT_STATUS);
	}
	else if(is_valid_exit(args[1]) == -1) // if not numeric 
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	else if(i > 2) // if many args
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		G_EXIT_STATUS = 1;
		return;
	}
	else // exit with the valid number
	{
		ft_putstr_fd("exit\n", 2);
		G_EXIT_STATUS = ft_atoi(args[1]);
		exit(G_EXIT_STATUS);
	}
}



/*
exit N (with number):

Exits with the specified exit code N
Numbers are taken modulo 256 (so exit 300 becomes exit 44)
Negative numbers wrap around (exit -1 becomes exit 255)
*/

/*
hind@hind-HP-EliteBook-820-G3:~/Desktop/MiniiShell$ exit 121232313123123131231313
exit
bash: exit: 121232313123123131231313: numeric argument required
*/

/* 
exit -9223372036854775808 -> exit(0)
*/

