/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:04:42 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:35:23 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection_type(enum e_type type)
{
	return (type == REDIR_OUT || type == REDIR_IN || type == HERE_DOC
		|| type == DREDIR_OUT);
}

t_parsing	*handle_redirection_errors(t_parsing *curr)
{
	if (curr->next && curr->type == REDIR_IN && curr->next->type == REDIR_OUT)
		return (error_print("syntax error  `newline'\n"), NULL);
	curr = curr->next;
	if (!curr)
		return (error_print("syntax error `newline'\n"), NULL);
	if (curr->type == '|')
		return (error_print("syntax error `|'\n"), NULL);
	if (is_redirection_type(curr->type))
	{
		error_print("syntax error '");
		ft_putstr_fd(curr->content, 2);
		return (ft_putstr_fd("'\n", 2), NULL);
	}
	return (curr);
}

t_parsing	*handle_pipe_errors(t_parsing *curr)
{
	curr = curr->next;
	if (!curr)
		return (error_print("syntax error `newline'\n"), NULL);
	if (is_redirection_type(curr->type))
		return (error_print("syntax error `newline'\n"), NULL);
	return (curr);
}

t_parsing	*check_redirection(t_parsing *head)
{
	t_parsing	*curr;
	t_parsing	*result;

	curr = head;
	if (!curr)
		return (NULL);
	if (is_redirection_type(curr->type))
	{
		result = handle_redirection_errors(curr);
		if (!result)
			return (NULL);
	}
	else if (curr->type == PIPE_LINE)
	{
		result = handle_pipe_errors(curr);
		if (!result)
			return (NULL);
	}
	return (head);
}
