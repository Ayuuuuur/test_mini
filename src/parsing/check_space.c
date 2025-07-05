/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/07/04 18:35:57 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing	*check_space(t_parsing *head)
{
	while (head)
	{
		if (head->type != WHITE_SPACE)
			return (head);
		head = head->next;
	}
	return (head);
}
