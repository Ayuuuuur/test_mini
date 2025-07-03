#include "../../includes/minishell.h"

void free_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_env **head_env)
{
	t_env	*temp;
	t_env	*next;

	temp = (*head_env);
	while (temp != NULL)
	{
		next = temp->next;
		if(temp->key)
			free(temp->key);
		if(temp->value)
			free(temp->value);
		free(temp);
		temp = next;
	}
	(*head_env) = NULL;
}

void free_node(t_env *node)
{
	if(node->value != NULL)
		free(node->value);
	free(node->key);
	free(node);
}

void	free_list_cmd(t_cmd **cmd_list)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = (*cmd_list);
	while (temp != NULL)
	{
		next = temp->next;
		free_arr_b((void **)(temp->full_cmd));
		free(temp);
		temp = next;
	}
	(*cmd_list) = NULL;
}
