#include "../../../includes/minishell.h"

char *join_key_value(t_env *temp)
{
	char	*key;
	char	*key_value;

	key = ft_strjoin(temp->key, "=", temp);
	if(!key)
		return(NULL);
	if(!temp->value)
		return(key);
	else
	{
		key_value = ft_strjoin(key, temp->value, temp);
		// free(key);
		if(!key_value)
			return(NULL);
		return(key_value);
	}
}

int	len_list(t_env *temp)
{
	int i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return(i);
}

char **envs_to_array(t_env *envs)
{
	char	**env_arr;
	int		i;

	i = len_list(envs);
	if(!envs)
		return(NULL);
	env_arr = (char **)g_collector(sizeof(char *) * (i + 1), envs);
	if(!env_arr)	
		return(NULL);
	i = 0;
	while (envs)
	{
		env_arr[i] = join_key_value(envs);
		if(!env_arr[i])
			return(NULL);
		i++;
		envs = envs->next;
	}
	env_arr[i] = NULL;
	return(env_arr);
}

int	len_list_cmd(t_cmd *temp)
{
	int i;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return(i);
}
