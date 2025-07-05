/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:35:55 by marvin            #+#    #+#             */
/*   Updated: 2025/07/04 18:21:56 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_dollar_sign_1(char *str, t_var *data, t_env *envp)
{
	int	result;

	data->j = data->i + 1;
	result = handle_special_cases(str, data, envp);
	if (result == 1)
		return (1);
	if (str[data->j] == '\0')
	{
		data->s1 = join_char(data->s1, '$', envp);
		if (!data->s1)
			return (2);
		return (0);
	}
	result = handle_parentheses(str, data, envp);
	if (result)
		return (result);
	result = handle_single_parentheses(str, data, envp);
	if (result)
		return (result);
	return (handle_env_variable_1(str, data, envp));
}

int	init_data_string(t_var *data, t_env *envp)
{
	data->s1 = g_collector(2, envp);
	if (!data->s1)
		return (2);
	data->s1[0] = '\0';
	data->i = 0;
	return (0);
}

int	process_regular_char(char *str, t_var *data, t_env *envp)
{
	data->s1 = join_char(data->s1, str[data->i], envp);
	if (!data->s1)
		return (2);
	return (0);
}

int	process_dollar_sign(char *str, t_var *data, t_env *envp)
{
	int	result;

	result = handle_dollar_sign_1(str, data, envp);
	if (result == 2)
		return (2);
	if (result == 1)
		return (1);
	return (0);
}

int	ft_double(char *str, t_env *envp, t_var *data)
{
	int	result;

	result = init_data_string(data, envp);
	if (result == 2)
		return (2);
	while (str[data->i])
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
				continue ;
		}
		data->i++;
	}
	return (0);
}
