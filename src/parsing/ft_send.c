/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:23:37 by marvin            #+#    #+#             */
/*   Updated: 2025/07/05 15:58:31 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*allocate_cmd_struct(t_var *data, t_env *envs)
{
	t_cmd	*cmd;

	cmd = g_collector(sizeof(t_cmd), envs);
	if (!cmd || data->s == NULL || data->l == 0)
		return (NULL);
	cmd->full_cmd = g_collector((data->l + 1) * sizeof(char *), envs);
	if (!cmd->full_cmd)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

void	populate_cmd_array(t_cmd *cmd, t_var *data, t_env *envs)
{
	int	i;

	i = 0;
	while (i < data->l)
	{
		cmd->full_cmd[i] = ft_strdup(data->s[i], envs);
		i++;
	}
	cmd->full_cmd[data->l] = NULL;
}

void	set_cmd_properties(t_cmd *cmd, t_var *data)
{
	cmd->out_file = data->out_file;
	cmd->in_file = data->in_file;
	cmd->next = NULL;
}

t_cmd	*append_to_cmd_list(t_cmd *head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!head)
		return (new_cmd);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
	return (head);
}

t_cmd	*ft_send(t_var *data, t_cmd *head, t_env *envs)
{
	t_cmd	*cmd;

	cmd = allocate_cmd_struct(data, envs);
	if (!cmd)
		return (NULL);
	populate_cmd_array(cmd, data, envs);
	set_cmd_properties(cmd, data);
	return (append_to_cmd_list(head, cmd));
}
