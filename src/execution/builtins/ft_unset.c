/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:16:52 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:16:52 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_unset(char **args, t_env **envs)
{
	t_env (*temp);
	t_env (*prev);
	int (i);
	i = 1;
	while (args[i])
	{
		temp = (*envs);
		prev = NULL;
		while (temp)
		{
			if (ft_strcmp(args[i], temp->key) == 0)
			{
				if (prev == NULL)
					(*envs) = temp->next;
				else
					prev->next = temp->next;
				free_node(temp);
				break ;
			}
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	return (g_exit_status = 0);
}
