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
void check_export(t_parsing **t)
{
    char *str;
    while(*t)
    {
        if(ft_strcmp(*t->content,"export") == 0)
        {
            *t = t->next;
            while(t)
            {
                if(ft_strchr(t->content,'=') == 0 && t->next && t->next->type != WHITE_SPACE)
                {
                    str = ft_strdup(t->content);
                    t->content = ft_strdup("");
                    t = t->next;
                    if(t->type == DQUOTE || t->type == QUOTE)
                        t = t->next;
                    t->content = ft_strjoin(str,t->content);
                }
                t = t->next;            
            }
            if(!t)
                return;
        }
        t = t->next;
    }
}
int check_expand(t_parsing *head,t_env *envp,int len,t_cmd **cmd)
{
    t_var data;
    t_parsing *t;

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
    t = head;
    check_export(t);
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