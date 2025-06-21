/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:31:05 by himousta          #+#    #+#             */
/*   Updated: 2024/11/13 21:00:27 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*nextnode;

	current = (*lst);
	while (current != 0)
	{
		nextnode = current->next;
		ft_lstdelone(current, del);
		current = nextnode;
	}
	(*lst) = NULL;
}
