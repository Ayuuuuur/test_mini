#include "../../includes/minishell.h"

t_env *new_env(char *env)
{
	t_env	*newnode;
	char 	*value;
	char 	**key;
	
	newnode = (t_env *)malloc(sizeof(t_env));
	if(!newnode)
		return(NULL);
	
	if(ft_strchr(env, '=') != NULL)
	{
		value = ft_strchr(env, '='); // search for the fisrt (=) and return pointer to it
		key = ft_split(env, '='); // split the command with (=);
		if(!key)
			return(NULL);
	}
	else
	{
		newnode->key = ft_strdup(env); //duplicate env 
		newnode->value = NULL; // no value. 
		newnode->flag_exported = 0; //if just the key (false)
		newnode->next = 0;
		return(newnode);
	}
	newnode->key = ft_strdup(key[0]); //duplicate the first argument
	newnode->value = ft_strdup(value + 1); //dup the string, +1 to skiip (=), like (=/hind/....)
	newnode->flag_exported = 1; //if has a value (true)
	newnode->next = 0;

	free_2d(key);
	return(newnode);
}

void add_env(t_env *newnode, t_env **head_list)
{
	t_env *temp;

	temp = (*head_list);
	if(temp ==  0)
	{
		(*head_list) = newnode;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = newnode;
	}
}

t_env  *list_envs(char **envp)
{
	t_env	*head_env;
	t_env	*newnode;
	int		i;

	head_env = 0;
	i = 0;
	if(!envp)
		return(NULL);
	while (envp[i])
	{
		newnode = new_env(envp[i]);
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


