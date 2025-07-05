/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/06/22 12:00:00 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing	*loop_expand(t_parsing *current, t_env *envp, t_var *data,
		char **concatenated_value)
{
	int	res;

	while (check_state_exp(current) == 1)
	{
		if (if_helper(&current) == 1)
			continue ;
		if (!help_concat(concatenated_value, current, envp, data))
			return (NULL);
		if (!current->next)
			break ;
		current = current->next;
		res = helper_loop_two(current);
		if (res == 2 || res == 1)
		{
			if (res == 1)
				continue ;
			break ;
		}
	}
	return (current);
}

t_parsing	*retun_expand(t_parsing *head, t_env *envp, t_var *data,
		t_cmd **cmd)
{
	t_parsing	*current;
	char		*concatenated_value;

	concatenated_value = ft_strdup("", envp);
	current = head;
	if (current->type == DQUOTE || current->type == QUOTE)
	{
		current = current->next;
	}
	current = loop_expand(current, envp, data, &concatenated_value);
	if (concatenated_value && ft_strlen(concatenated_value) > 0)
	{
		data->s[data->l] = concatenated_value;
		data->l++;
	}
	if (current && current->type == PIPE_LINE)
		return (check_pipe_expand(current, data, cmd, envp));
	if (current)
		return (current);
	return (head);
}

t_parsing	*expand(t_parsing *head, t_env *envp, t_var *data, t_cmd **cmd)
{
	if (!head)
		return (NULL);
	if (!head->content)
		return (head);
	head = check_space(head);
	if (!head)
		return (NULL);
	if (head->type == PIPE_LINE)
		return (check_pipe_expand(head, data, cmd, envp));
	else if (head->type == REDIR_IN)
		return (check_redin_expand(head, data));
	else if (head->type == HERE_DOC)
		return (check_herdoc_expand(head, data, envp));
	else if (head->type == DREDIR_OUT || head->type == REDIR_OUT)
		return (check_redout_expand(head, data));
	else if (is_standalone_env_var(head))
		return (check_env_expand(head, data, envp));
	if (head->type == DQUOTE || head->type == QUOTE || head->type == WORD
		|| head->state == 2 || head->state == 3)
		return (retun_expand(head, envp, data, cmd));
	return (head);
}
