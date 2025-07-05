/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:14:28 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:28:51 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	extract_var_name(char *str, t_var *data, char **var_name)
{
	int	start;
	int	len;

	start = data->j;
	while (str[data->j] && (ft_isalnum(str[data->j]) || str[data->j] == '_'))
		data->j++;
	len = data->j - start;
	if (len > 0)
	{
		*var_name = ft_substr(str, start, len);
		if (!*var_name)
			return (2);
		return (1);
	}
	return (0);
}

char	*find_env_value(char *var_name, t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var_name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	handle_valid_var(t_var *data, char *var_value, t_env *envp)
{
	data->s1 = ft_strjoin(data->s1, var_value, envp);
	if (!data->s1)
		return (2);
	data->i = data->j - 1;
	return (0);
}

int	handle_invalid_var(t_var *data, t_env *envp)
{
	data->s1 = join_char(data->s1, '$', envp);
	if (!data->s1)
		return (2);
	data->i = data->i;
	return (0);
}

int	handle_env_variable_1(char *str, t_var *data, t_env *envp)
{
	char	*var_name;
	char	*var_value;
	int		extract_result;
	int		result;

	extract_result = extract_var_name(str, data, &var_name);
	if (extract_result == 2)
		return (2);
	if (extract_result == 1)
	{
		var_value = find_env_value(var_name, envp);
		if (var_value)
			result = handle_valid_var(data, var_value, envp);
		else
			result = handle_valid_var(data, "", envp);
		free(var_name);
		return (result);
	}
	else
	{
		return (handle_invalid_var(data, envp));
	}
}
