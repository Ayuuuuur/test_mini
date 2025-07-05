/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:27:54 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/05 17:59:33 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_env_split(t_parsing *head, t_env *envp, t_var *data)
{
	char	*expanded_value;
	char	**split_env;

	expanded_value = check_env_general(head->content, envp);
	if (!expanded_value)
		return (0);
	if (ft_strchr(expanded_value, ' '))
	{
		split_env = ft_split(expanded_value, ' ', envp);
		if (!split_env)
			return (0);
		return (add_split_tokens(split_env, data, envp));
	}
	else
	{
		if (ft_strlen(expanded_value) > 0)
		{
			data->s[data->l] = expanded_value;
			data->l++;
		}
		return (1);
	}
}

char	*get_token_value(t_parsing **head, t_env *envp, t_var *data)
{
	if (!(*head) || !(*head)->content)
		return (ft_strdup("", envp));
	if ((*head)->state == 3)
		return (check_env_general((*head)->content, envp));
	else if ((*head)->state == 2)
	{
		if (ft_double(head, envp, data) == 2)
			return (NULL);
		if (data->s1)
			return (ft_strdup(data->s1, envp));
		else
			return (ft_strdup("", envp));
	}
	else if ((*head)->state == 1)
		return (ft_strdup((*head)->content, envp));
	else if ((*head)->state == 0 && (*head)->type == WORD)
		return (ft_strdup((*head)->content, envp));
	return (ft_strdup("", envp));
}

t_parsing	*handle_heredoc(t_parsing *head, t_var *data, t_env *envp)
{
	int	flag;

	flag = 0;
	head = head->next;
	if (!head)
		return (NULL);
	if (head->type == WHITE_SPACE)
		head = head->next;
	if (head->type == DQUOTE || head->type == QUOTE)
	{
		flag = 1;
		head = head->next;
	}
	return (heredoce(head, data, flag, envp));
}

t_parsing	*handle_redirect_out(t_parsing *head, t_var *data)
{
	if (ft_redirect_out(head, data) == 2)
		return (NULL);
	head = head->next;
	head = check_space(head);
	return (head);
}

t_parsing	*check_redir_herdoc(t_parsing *head, t_var *data, t_env *envp)
{
	if (head->type == HERE_DOC)
		return (handle_heredoc(head, data, envp));
	if (head->type == DREDIR_OUT || head->type == REDIR_OUT)
		return (handle_redirect_out(head, data));
	return (head);
}
