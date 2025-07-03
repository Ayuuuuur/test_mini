

#include "../../../includes/minishell.h"

int	ft_builtin(char **command, int is_child, t_env **envs)
{
	if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(command, (*envs)), 0);
	else if (ft_strcmp(command[0], "pwd") == 0)
		return (ft_pwd((*envs)), 0);
	else if(ft_strcmp(command[0], "env") == 0)
		return(ft_env(command ,(*envs)), 0);
	else if(ft_strcmp(command[0], "exit") == 0)
		return(ft_exit(command, is_child, (*envs)), 0);
	else if(ft_strcmp(command[0], "unset") == 0)
		return(ft_unset(command, envs), 0);
	else if(ft_strcmp(command[0], "export") == 0)
		return(ft_export(command, envs), 0);
	else if(ft_strcmp(command[0], "echo") == 0)
		return(ft_echo(command), 0);
	else
		return(-1);
}
