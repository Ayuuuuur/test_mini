#include "../../../includes/minishell.h"


char **creat_mini_envp()
{
	char	**minimal_envp;

	minimal_envp = malloc(sizeof(char *) * 5);
	minimal_envp[0] = ft_strdup_env("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	minimal_envp[1] = ft_strdup_env("OLDPWD");
	minimal_envp[2] = get_pwd();
	minimal_envp[3] = ft_strdup_env("SHLVL=1");
	minimal_envp[4] = NULL;
	return(minimal_envp);
}

t_env *split_key_value(int is_path_exported, char *env, t_env *newnode, char **envp)
{
	char 		*value;
	char 		**key;

	value = ft_strchr(env, '='); // search for the fisrt (=) and return pointer to it
	key = ft_split_env(env, '='); // split the command with (=);
	if(!key)
		return(NULL);
	newnode->key = ft_strdup_env(key[0]); //duplicate the first argument
	newnode->value = ft_strdup_env(value + 1); //dup the string, +1 to skiip (=), like (=/hind/....)
	newnode->next = 0;
	newnode->head_gc = NULL; // no garbage collector
	free_2d(key);
	if(ft_strcmp(newnode->key, "PATH") == 0 && (!envp || !envp[0]) && !is_path_exported) // flaged with 2 to not printed in (env, export)
	{
		newnode->flag_exported = 2;
		is_path_exported = 1;
	}
	else
		newnode->flag_exported = 1; //if has a value (true)
	return(newnode);
}

t_env *new_env(char *env, char **envp)
{
	static int 	is_path_exported;
	t_env		*newnode;
	
	newnode = (t_env *)malloc(sizeof(t_env));
	if(!newnode)
		return(NULL);
	if(ft_strchr(env, '=') != NULL)
		newnode = split_key_value(is_path_exported, env, newnode, envp);
	else
	{
		newnode->key = ft_strdup_env(env); //duplicate env 
		newnode->value = NULL; // no value. 
		newnode->flag_exported = 0; //if just the key (false)
		newnode->next = 0;
		newnode->head_gc = NULL; // no garbage collector
	}
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

char *get_pwd()
{
	char *working_d;
	char *complet_pwd;

	working_d = getcwd(NULL, 0);
	if(!working_d)
	{
		perror("minishell");
		return(NULL);
	}
	complet_pwd = ft_strjoin_env("PWD=", working_d);
	free(working_d);
	return(complet_pwd);
}
