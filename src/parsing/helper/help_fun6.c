/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:28:49 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 16:28:51 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing	*check_redin_expand(t_parsing *head, t_var *data)
{
	if (ft_redirect_in(head, data) == 2)
		return (NULL);
	head = head->next;
	head = check_space(head);
	return (head);
}

t_parsing	*check_pipe_expand(t_parsing *head, t_var *data, t_cmd **cmd,
		t_env *envp)
{
	*cmd = ft_send(data, *cmd, envp);
	data->l = 0;
	data->in_file = -1;
	data->out_file = -1;
	return (head);
}

t_parsing	*check_herdoc_expand(t_parsing *head, t_var *data, t_env *envp)
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

t_parsing	*check_redout_expand(t_parsing *head, t_var *data)
{
	if (ft_redirect_out(head, data) == 2)
		return (NULL);
	head = head->next;
	head = check_space(head);
	return (head);
}

t_parsing	*check_env_expand(t_parsing *head, t_var *data, t_env *envp)
{
	if (!handle_env_split(head, envp, data))
		return (NULL);
	return (head);
}
