/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:35:44 by nahilal           #+#    #+#             */
/*   Updated: 2025/04/29 18:54:44 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *ft_save(char *av,t_parsing *head,enum e_type type,char c,enum e_state state, t_env *envs)
{
    t_parsing *data = g_collector(sizeof(t_parsing), envs);
    t_parsing *current = NULL;
    if(!data)
        return (NULL);
    if(c == 0 || c == -2 || c == -3)
        data->content = av;
    else
    {
        data->content = g_collector(2, envs);
        data->content[0] = c;   
        data->content[1] = 0;   
    }
    data->state = state;
    data->type = type;
    data->next = NULL;
    if (!head)
        return (data);
    current = head;
    while (current->next)
        current = current->next;
    current->next = data;

    return head;
}

