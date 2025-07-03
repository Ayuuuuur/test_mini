#include "../../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break;	
		i++;
	}
	return (s1[i] - s2[i]);
}

int ft_unset(char **args, t_env **envs)
{
	int i;
	
	t_env (*temp), (*prev);
	i = 1; // skip unset
	while (args[i])
	{
		temp = (*envs);
		prev = NULL;
		while (temp)
		{
			if(ft_strcmp(args[i], temp->key) == 0)
			{
				if(prev == NULL) // if null , fist node
					(*envs) = temp->next;
				else
					prev->next = temp->next;
				free_node(temp);
				break;
			}
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	return(G_EXIT_STATUS = 0);
}
