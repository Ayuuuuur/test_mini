#include "../../../includes/minishell.h"

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (i < len && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_env(const char *s1)
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


t_env  *list_envs(char **envp)
{
	char	**minimal_envp;

	if(!envp) // if all envps removed 
		return(NULL);
	else if(envp[0] == NULL) // cuz a char *envp[] = { NULL }; (start with minimal envps)
	{
		minimal_envp = creat_mini_envp();
		return(build_new_envs(minimal_envp, envp));
	}
	else
		return(build_new_envs(envp, envp));
}


t_env  *build_new_envs(char **envs, char **envp)
{
	t_env	*head_env;
	t_env	*newnode;
	int i;

	head_env = 0;
	i = 0;
	while (envs[i])
	{
		newnode = new_env(envs[i], envp);
		if(!newnode)
		{
			free_list(&head_env); //garbeg coll
			return(NULL);
		}
		add_env(newnode, &head_env);
		i++;
	}
	return(head_env);
}

