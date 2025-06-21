/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:23:37 by marvin            #+#    #+#             */
/*   Updated: 2025/05/23 18:23:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *ft_send(t_var *data, t_cmd *head)
{
    t_cmd *cmd;
    t_cmd *current = NULL;
    int i;
    
    cmd = malloc(sizeof(t_cmd));
    i = 0;
    if (!cmd || data->s[i] == NULL || data->l == 0)
        return (NULL);
    cmd->full_cmd = malloc((data->l + 1) * sizeof(char *));
    if (!cmd->full_cmd)
    {
        free(cmd);
        return (NULL);
    }
    while(i < data->l)
    {
        cmd->full_cmd[i] = ft_strdup(data->s[i]);
        i++;
    }
    cmd->full_cmd[data->l] = NULL;
    cmd->out_file = data->out_file;
    cmd->in_file = data->in_file;
    cmd->next = NULL;
    if (!head)
        return (cmd);
    current = head;
    while (current->next)
        current = current->next;
    current->next = cmd;
    return (head);
}