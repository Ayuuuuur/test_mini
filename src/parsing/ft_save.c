/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:35:44 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:35:34 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing	*create_parsing_node(t_lexer_data *data, t_env *envs)
{
	t_parsing	*node;

	node = g_collector(sizeof(t_parsing), envs);
	if (!node)
		return (NULL);
	node->state = data->state;
	node->type = data->token_type;
	node->next = NULL;
	return (node);
}

void	set_node_content(t_parsing *node, t_lexer_data *data, t_env *envs)
{
	if (data->char_value == 0 || data->char_value == -2
		|| data->char_value == -3)
		node->content = data->content_str;
	else
	{
		node->content = g_collector(2, envs);
		node->content[0] = data->char_value;
		node->content[1] = 0;
	}
}

t_parsing	*append_to_list(t_parsing *head, t_parsing *new_node)
{
	t_parsing	*current;

	if (!head)
		return (new_node);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (head);
}

t_parsing	*ft_save(t_lexer_data *data, t_parsing *head, t_env *envs,
		char *content)
{
	t_parsing	*node;

	data->content_str = content;
	node = create_parsing_node(data, envs);
	if (!node)
		return (NULL);
	set_node_content(node, data, envs);
	return (append_to_list(head, node));
}
