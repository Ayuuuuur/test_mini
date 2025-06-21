/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:04:42 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/02 17:54:52 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *check_redirection(t_parsing *head)
{
    t_parsing *curr;

    curr = head;
    if(!curr)
        return(NULL);
    if(curr->type == REDIR_OUT || curr->type == REDIR_IN
        || curr->type == HERE_DOC || curr->type == DREDIR_OUT)
    {
        if(curr->next && curr && curr->type == REDIR_IN && curr->next->type == REDIR_OUT)
            return(error_print("syntax error near unexpected token `newline'\n"),NULL);
        curr = curr->next;
        if(!curr)
            return(error_print("syntax error near unexpected token `newline'\n"),NULL);
        if(curr->type == '|')
            return(error_print("syntax error near unexpected token `|'\n"),NULL);
        if(curr->type == REDIR_IN || curr->type == HERE_DOC || curr->type == REDIR_OUT)
        {
            error_print("syntax error near unexpected token hello`");
            ft_putstr_fd(curr->content,2);
            return(ft_putstr_fd("'\n",2),NULL);
        }
    }
    else if(curr->type == PIPE_LINE)
    {
        curr = curr->next;
        if(!curr)
            return(error_print("syntax error near unexpected token `newline'\n"),NULL);
        else if(curr->type == REDIR_OUT || curr->type == REDIR_IN
            || curr->type == HERE_DOC || curr->type == DREDIR_OUT)
            return(error_print("syntax error near unexpected token `newline'\n"),NULL);
    }
    return(head);
}