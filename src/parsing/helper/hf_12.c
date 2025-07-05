/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hf_12.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:25:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:29:39 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing	*skip_whitespace(t_parsing *current)
{
	while (current && current->type == WHITE_SPACE)
		current = current->next;
	return (current);
}

t_parsing	*get_next_content_token(t_parsing *current)
{
	t_parsing	*next_token;

	next_token = current->next;
	if (next_token->type == DQUOTE || next_token->type == QUOTE)
		next_token = next_token->next;
	return (next_token);
}

int	should_merge_tokens(t_parsing *current)
{
	if (!current->content || !ft_strchr(current->content, '='))
		return (0);
	if (!current->next || current->next->type == WHITE_SPACE
		|| current->next->type == PIPE_LINE)
		return (0);
	return (1);
}

void	merge_export_tokens(t_parsing *current, t_env *envs)
{
	char		*str;
	char		*new_content;
	t_parsing	*next_token;

	str = ft_strdup(current->content, envs);
	if (!str)
		return ;
	next_token = get_next_content_token(current);
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

char	*build_delimiter(t_parsing *head, int *flag, t_env *envp)
{
	char	*delimiter;

	delimiter = ft_strdup(head->content, envp);
	head = head->next;
	while (head)
	{
		if (head->type == PIPE_LINE || head->type == SPACE)
			break ;
		if (head->type == DQUOTE || head->type == QUOTE)
			*flag = 1;
		else
			delimiter = ft_strjoin(delimiter, head->content, envp);
		head = head->next;
	}
	return (delimiter);
}
