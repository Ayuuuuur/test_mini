#include "../../../includes/minishell.h"

int ft_perror_env(char *str, int exit_stat)
{
	ft_putstr_fd(str, 2);
	G_EXIT_STATUS =  exit_stat;
	return(G_EXIT_STATUS);
}

int ft_env(char **args, t_env *envs)
{
	if(!envs || !get_env_value("PATH", envs))
		return(ft_perror_env("minishell: env: No such file or directory\n", 127));
	if(!executable_path("env", envs)) // in case we have path walakin mashi dyal env
		return(ft_perror_env("env: command not found\n", 127));
	if(args[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return(G_EXIT_STATUS = 127);
	}
	while (envs)
	{
		if(envs->flag_exported == 1)
		{	
			printf("%s", envs->key);
			printf("=");
			printf("%s\n", envs->value);
		}
		envs = envs->next;
	}
	return(G_EXIT_STATUS = 0);
}

