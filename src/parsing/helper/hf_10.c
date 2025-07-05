/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hf_10.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:20:21 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/05 19:18:21 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*init_result_string(t_env *envp)
{
	char	*result;

	result = ft_strdup("", envp);
	if (!result)
		return (NULL);
	return (result);
}

int	extract_var_name_length(char *line, int *i)
{
	int	start;
	int	len;

	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	len = *i - start;
	return (len);
}

char	*find_env_var_value(char *line, int start, int len, t_env *envp)
{
	t_env	*tmp;
	char	*var_name;

	tmp = envp;
	var_name = ft_substr(line, start, len, envp);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var_name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*process_dollar_variable(char *line, int *i, char *result, t_env *envp)
{
	int		start;
	int		len;
	char	*var_value;

	(*i)++;
	start = *i;
	len = extract_var_name_length(line, i);
	if (len > 0)
	{
		var_value = find_env_var_value(line, start, len, envp);
		if (var_value)
		{
			result = ft_strjoin(result, var_value, envp);
			if (!result)
				return (NULL);
		}
	}
	else
		result = ft_charjoin(result, '$', envp);
	return (result);
}

char	*expand_var(char *line, t_env *envp, int i)
{
	char	*result;

	if (!line)
		return (NULL);
	result = init_result_string(envp);
	if (!result)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			result = process_dollar_variable(line, &i, result, envp);
			if (!result)
				return (NULL);
		}
		else
		{
			result = join_char(result, line[i], envp);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}
