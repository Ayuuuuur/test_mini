/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fung7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:29:37 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/05 17:28:25 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	helper_loop_exp(t_parsing *current)
{
	t_parsing	*peek;

	if (current && (current->type == DQUOTE || current->type == QUOTE))
	{
		peek = current->next;
		if (peek && (peek->type == WORD || peek->state == 1 || peek->state == 2
				|| peek->state == 3))
			return (1);
		else
			return (2);
	}
	return (0);
}

int	helper_loop_two(t_parsing *current)
{
	int	res;

	res = helper_loop_exp(current);
	if (res == 2 || res == 1)
	{
		if (res == 1)
			return (1);
		return (2);
	}
	if (current && (current->type == WHITE_SPACE || current->type == PIPE_LINE
			|| current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == HERE_DOC || current->type == DREDIR_OUT))
	{
		return (2);
	}
	return (0);
}

int	if_helper(t_parsing **current)
{
	if ((*current)->type == DQUOTE || (*current)->type == QUOTE)
	{
		(*current) = (*current)->next;
		return (1);
	}
	return (0);
}

int	check_state_exp(t_parsing *current)
{
	if (current && (current->type == WORD || current->state == 1
			|| current->state == 2 || current->state == 3
			|| current->type == DQUOTE || current->type == QUOTE))
	{
		return (1);
	}
	return (0);
}

t_parsing	*help_concat(char **concatenated_value, t_parsing **current,
		t_env *envp, t_var *data)
{
	char	*new_concat;
	char	*temp_value;

	temp_value = get_token_value(current, envp, data);
	if (!temp_value)
		return (NULL);
	new_concat = ft_strjoin(*concatenated_value, temp_value, envp);
	if (!new_concat)
		return (NULL);
	*concatenated_value = new_concat;
	return ((*current));
}
