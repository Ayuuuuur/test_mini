/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:12:36 by marvin            #+#    #+#             */
/*   Updated: 2025/07/04 18:35:59 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	determine_redirect_type(t_parsing *head)
{
	int	t;

	t = DREDIR_OUT;
	if (head && head->type == REDIR_OUT)
		t = head->type;
	return (t);
}

t_parsing	*find_word_token(t_parsing *head)
{
	head = head->next;
	while (head)
	{
		if (head->type == WORD)
			break ;
		head = head->next;
	}
	return (head);
}

int	open_output_file(char *filename, int redirect_type)
{
	int	fd;

	if (redirect_type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_redirect_out(t_parsing *head, t_var *data)
{
	int			fd;
	int			redirect_type;
	t_parsing	*word_token;

	if (!head)
		return (2);
	redirect_type = determine_redirect_type(head);
	word_token = find_word_token(head);
	if (!word_token || !word_token->content)
		return (2);
	fd = open_output_file(word_token->content, redirect_type);
	if (fd == -1)
		return (2);
	data->out_file = fd;
	return (0);
}
