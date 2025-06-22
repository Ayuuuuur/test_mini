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

void check_export(t_parsing **head)
{
    t_parsing *current = *head;
    t_parsing *next_token;
    char *str;
    char *new_content;
    
    while (current)
    {
        // Check if current token is "export"
        if (current->content && ft_strcmp(current->content, "export") == 0)
        {
            current = current->next;
            
            // Skip whitespace after export
            while (current && current->type == WHITE_SPACE)
                current = current->next;
            
            // Process each argument after export
            while (current && current->type != PIPE_LINE)
            {
                // Skip whitespace
                while (current && current->type == WHITE_SPACE)
                    current = current->next;
                
                if (!current || current->type == PIPE_LINE)
                    break;
                
                // Check if this token has '=' but the next token is not whitespace
                if (current->content && ft_strchr(current->content, '=') && 
                    current->next && current->next->type != WHITE_SPACE &&
                    current->next->type != PIPE_LINE)
                {
                    str = ft_strdup(current->content);
                    if (!str)
                        return;
                    
                    next_token = current->next;
                    
                    // Skip quotes if present
                    if (next_token->type == DQUOTE || next_token->type == QUOTE)
                        next_token = next_token->next;
                    
                    if (next_token && next_token->content)
                    {
                        // Concatenate the current token with the next token
                        new_content = ft_strjoin(str, next_token->content);
                        if (new_content)
                        {
                            // Update current token content
                            free(current->content);
                            current->content = new_content;
                            
                            // Mark the next token for skipping by setting content to NULL
                            free(next_token->content);
                            next_token->content = NULL;
                        }
                        free(str);
                    }
                    else
                    {
                        free(str);
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
        data.s = malloc(1 * sizeof(char *));
        data.s[0] = NULL;
    }
    else
        data.s = malloc(len*10 * sizeof(char *));   
    data.l = 0;
    data.in_file = -1;
    data.out_file = -1;
    check_export(&head);
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