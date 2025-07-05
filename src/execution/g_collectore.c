/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collectore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:02:28 by hind              #+#    #+#             */
/*   Updated: 2025/07/05 19:42:20 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*g_collector(size_t size, t_env *envs)
{
	t_gc		*temp;
	t_gc		*new_collect;
	void		*allocated;

	allocated = malloc(size);
	if (!allocated)
		return (clean_and_null(envs));
	new_collect = malloc(sizeof(t_gc));
	if (!new_collect)
		return (clean_and_null(envs));
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
	return (allocated);
}

char	*clean_and_null(t_env *envs)
{
	clean_memory(&(envs->head_gc));
	return (NULL);
}

void	clean_memory(t_gc **head)
{
	t_gc	*temp;
	t_gc	*next;

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
