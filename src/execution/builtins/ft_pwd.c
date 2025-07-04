#include "../../../includes/minishell.h"

int ft_pwd(t_env *envs)
{
	char *working_d;
	int should_free = 0;

	working_d = getcwd(NULL, 0);
	if(working_d == NULL)
	{
		working_d = get_env_value("PWD", envs);
		if(!working_d)
		{
			perror("minishell");
			return(EXIT_FAILURE);
		}
		should_free = 0; // Don't free env value
	}
	else
	{
		should_free = 1; // Free getcwd allocated memory
	}
	
	printf("%s\n", working_d);
	
	if(should_free)
		free(working_d);
	
	g_exit_status = 0;
	return(EXIT_SUCCESS);
}