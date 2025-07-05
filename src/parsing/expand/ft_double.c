/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:35:55 by marvin            #+#    #+#             */
/*   Updated: 2025/07/05 19:14:25 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	double_concat(t_parsing **head, char **str, t_env *envp)
{
	t_parsing	*tmp;

	tmp = (*head);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type != DQUOTE)
		{
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp && tmp->state == 2)
	{
		*str = ft_strjoin(*str, tmp->content, envp);
		*head = tmp;
	}
}

int	check_dloop(char *str, t_var *data, t_env *envp, int result)
{
	if (str[data->i] != '$')
	{
		result = process_regular_char(str, data, envp);
		if (result == 2)
			return (2);
	}
	else
	{
		result = process_dollar_sign(str, data, envp);
		if (result == 2)
			return (2);
		if (result == 1)
			return (1);
	}
	return (0);
}

int	ft_double(t_parsing **head, t_env *envp, t_var *data)
{
	char	*str;
	int		result;
	int		res;

	str = (*head)->content;
	double_concat(head, &str, envp);
	result = init_data_string(data, envp);
	if (result == 2)
		return (2);
	while (str[data->i])
	{
		res = check_dloop(str, data, envp, result);
		if (res == 2)
			return (2);
		if (res == 1)
			continue ;
		data->i++;
	}
	return (0);
}
