#include "../../includes/minishell.h"

void *g_collector(size_t size, t_env *envs)
{
	t_gc		*temp;
	t_gc		*new_collect;
	void		*allocated;

	allocated = malloc(size);
	if(!allocated)
		return(clean_and_NULL(envs));
	new_collect = malloc(sizeof(t_gc)); // allocate the new node
	if(!new_collect)
		return(clean_and_NULL(envs));
	new_collect->node = allocated;
	new_collect->next = NULL;
	if (envs->head_gc == NULL)
		envs->head_gc = new_collect;
	else
	{
		temp = envs->head_gc;
		while (temp->next)
			temp = temp->next;
		temp->next = new_collect;
	}
	return(allocated);
}

char *clean_and_NULL(t_env *envs)
{
	clean_memory(&(envs->head_gc)); // call to clear_memory // return with null or somethingg 
	return(NULL);
}

void clean_memory(t_gc **head)
{
	t_gc *temp;
	t_gc *next;

	temp = (*head);
	while (temp)
	{
		next = temp->next;
		free(temp->node);
		free(temp);
		temp = next;
	}
	*head = NULL;
}


