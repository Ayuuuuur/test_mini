/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:22 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:22:32 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	process_export_tokens(t_parsing *current, t_env *envs)
{
	while (current && current->type != PIPE_LINE)
	{
		current = skip_whitespace(current);
		if (!current || current->type == PIPE_LINE)
			break ;
		if (should_merge_tokens(current))
			merge_export_tokens(current, envs);
		current = current->next;
	}
}

void	check_export(t_parsing **head, t_env *envs)
{
	t_parsing	*current;

	current = *head;
	while (current)
	{
		if (current->content && ft_strcmp(current->content, "export") == 0)
		{
			current = current->next;
			current = skip_whitespace(current);
			process_export_tokens(current, envs);
		}
		else
		{
			current = current->next;
		}
	}
}

int	check_expand(t_parsing *head, t_env *envp, int len, t_cmd **cmd)
{
	t_var	data;

	if (len == 0)
		data.s = NULL;
	else
		data.s = g_collector(len * 10 * sizeof(char *), envp);
	data.l = 0;
	data.in_file = -1;
	data.out_file = -1;
	check_export(&head, envp);
	while (head)
	{
		head = expand(head, envp, &data, cmd);
		if (!head)
			return (2);
		head = head->next;
	}
	*cmd = ft_send(&data, *cmd, envp);
	return (0);
}
