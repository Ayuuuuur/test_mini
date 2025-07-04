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


void check_export(t_parsing **head, t_env *envs)
{
    t_parsing *current = *head;
    t_parsing *next_token;
    char *str;
    char *new_content;
    
    while (current)
    {
        if (current->content && ft_strcmp(current->content, "export") == 0)
        {
            current = current->next;
            while (current && current->type == WHITE_SPACE)
                current = current->next;
            while (current && current->type != PIPE_LINE)
            {
                while (current && current->type == WHITE_SPACE)
                    current = current->next;
                if (!current || current->type == PIPE_LINE)
                    break;
                if (current->content && ft_strchr(current->content, '=') && 
                    current->next && current->next->type != WHITE_SPACE &&
                    current->next->type != PIPE_LINE)
                {
                    str = ft_strdup(current->content, envs);
                    if (!str)
                        return;
                    next_token = current->next;
                    if (next_token->type == DQUOTE || next_token->type == QUOTE)
                        next_token = next_token->next;
                    if (next_token && next_token->content)
                    {
                        new_content = ft_strjoin(str, next_token->content, envs);
                        if (new_content)
                        {
                            current->content = new_content;
                            next_token->content = NULL;
                        }
                    }
                }
                current = current->next;
            }
        }
        else
        {
            current = current->next;
        }
    }
}

int check_expand(t_parsing *head,t_env *envp,int len,t_cmd **cmd)
{
    t_var data;

    if(len == 0)
    {
        data.s = g_collector(1 * sizeof(char *), envp);
        data.s[0] = NULL;
    }
    else
        data.s = g_collector(len*10 * sizeof(char *), envp);   
    data.l = 0;
    data.in_file = -1;
    data.out_file = -1;
    check_export(&head, envp);
    while(head)
    {
        head = expand(head,envp,&data,cmd);
        if(!head)
        {
            printf("heeeere\n");
            return(2);
        }
        head = head->next;
    }
    *cmd = ft_send(&data,*cmd, envp);
    return(0);
}