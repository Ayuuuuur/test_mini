#include "../../../includes/minishell.h"

int  exist_env(t_env *newnode, t_env *temp_env)
{
	while (temp_env)
	{
		if(ft_strcmp(temp_env->key, newnode->key) == 0 && temp_env->flag_exported == 1 
			&& newnode->value == NULL) //if exist (key=value) and (export key)
			return(0);

		if(ft_strcmp(temp_env->key, newnode->key) == 0) //if exist (tem->key == newn->key)
		{
			if(temp_env->value != NULL) //if old value set it as NULL (like, ZZZ)
				free(temp_env->value); // free old value 
			temp_env->value = ft_strdup(newnode->value); //dup the new value or NULL
			temp_env->flag_exported = newnode->flag_exported; //update flage
			return (0);
		}
		temp_env = temp_env->next;
	}
	return(1);
}

void	print_env_list(t_env *head)
{
	while (head)
	{
		if(head->flag_exported == 1)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
}

int valide_name(char *str)
{
	int i;

	i = 0;
	if((str[i] < 'a' || str[i] > 'z') &&  //first charactere ..
		(str[i] < 'A' || str[i] > 'Z') &&
		str[i] != '_')
		return(-1);
	i++; // to skip first character 
	while (str[i] && str[i] != '=')
	{
		if((str[i] < 'a' || str[i] > 'z') &&
			(str[i] < 'A' || str[i] > 'Z') &&
			(str[i] < '0' || str[i] > '9') &&
			str[i] != '_')
			return(-1);
		i++;
	}
//	if(str[i] != '=') //check if we have just a name without '='
// 		return(-2);
	return(0);
}

int ft_export(char **args, t_env **envs)
{
	t_env	*newnode;
	int		i;

	i = 1;
	while (args[i])
	{
		if(valide_name(args[i]) == -1)
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			G_EXIT_STATUS = 1;
		}
		else
		{
			newnode = new_env(args[i]);
			if(exist_env(newnode, (*envs)) == 0) //if env exit but change his value.
				free_node(newnode);
			else
		 		add_env(newnode, envs);
		}
		i++;
	}
	if(i == 1) // no args exist. 
		print_env_list(*envs);
	return(EXIT_SUCCESS);
}

