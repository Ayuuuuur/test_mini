/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:30:22 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/08 18:30:22 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int check_expand(t_parsing *head,t_env *envp,int len,t_cmd **cmd)
{
    t_var data;

    if(len == 0)
    {
        data.s = malloc(1 * sizeof(char *));
        data.s[0] = NULL;
    }
    else
        data.s = malloc(len*10 * sizeof(char *));   
    data.l = 0;
    data.in_file = -1;
    data.out_file = -1;
    while(head)
    {
        head = expand(head,envp,&data,cmd);
        if(!head)
        {
            return(2);
        }
        head = head->next;
    }
    *cmd = ft_send(&data,*cmd);
    return(0);
}