/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:44:05 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:35:20 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing	*skip_space(t_parsing *head)
{
	if (!head)
		return (NULL);
	while (head->type == ' ' && head)
		head = head->next;
	return (head);
}
