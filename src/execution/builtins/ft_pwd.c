#include "../../../includes/minishell.h"

int ft_pwd(t_env *envs)
{
	char *working_d;

	working_d = getcwd(NULL, 0);
	if(working_d == NULL)
	{
		working_d = get_env_value("PWD", envs);
		if(!working_d)
		{
			perror("minishell");
			return(EXIT_FAILURE);
		}
	}
	printf("%s\n", working_d);
	return(EXIT_SUCCESS);
}
