/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:12:40 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:28:12 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*join_char(char *str, char c, t_env *envs)
{
	char	*result;
	size_t	len;

	if (!str)
	{
		result = g_collector(2, envs);
		if (!result)
			return (NULL);
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	len = ft_strlen(str);
	result = g_collector(len + 2, envs);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

int	check_parth(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '(')
			len++;
		i++;
	}
	i = 0;
	while (str[i] && len >= 0)
	{
		if (str[i] == ')')
			len--;
		i++;
	}
	if (len != 0)
		return (0);
	return (2);
}

int	handle_special_cases(char *str, t_var *data, t_env *envp)
{
	if (str[data->j] == '$')
	{
		data->s1 = ft_strjoin(data->s1, "$$", envp);
		data->i = data->j + 1;
		return (1);
	}
	else if (str[data->j] == ' ')
	{
		data->s1 = join_char(data->s1, '$', envp);
		data->i = data->j - 1;
		return (1);
	}
	else if (str[data->j] == '?')
	{
		data->s1 = ft_strjoin(data->s1, ft_itoa(g_exit_status, envp), envp);
		data->i = data->j + 1;
		return (1);
	}
	return (0);
}

int	handle_parentheses(char *str, t_var *data, t_env *envp)
{
	if (str[data->j] == '(' && str[data->j + 1] == '(')
	{
		if (check_parth(str + data->i) == 0)
			return (error_print("syntax error \"unclosed parentheses\"\n"), 2);
		data->j += 2;
		while (str[data->j] != ')' || str[data->j + 1] != ')')
		{
			if (str[data->j] == '\0')
				return (error_print("syntax error \"unclosed parentheses\"\n"),
					2);
			data->j++;
		}
		data->s1 = ft_strjoin(data->s1, "0", envp);
		if (!data->s1)
			return (2);
		data->i = data->j + 2;
		return (1);
	}
	return (0);
}

int	handle_single_parentheses(char *str, t_var *data, t_env *envp)
{
	int	start;

	if (str[data->j] == '(')
	{
		if (check_parth(str + data->i) == 0)
			return (error_print("syntax error \"unclosed parentheses\"\n"), 2);
		data->j++;
		start = data->j;
		while (str[data->j] != ')')
		{
			if (str[data->j] == '\0')
				return (error_print("syntax error \"unclosed parentheses\"\n"),
					2);
			data->j++;
		}
		data->s1 = ft_strjoin(data->s1, ft_substr(str, start, data->j - start),
				envp);
		if (!data->s1)
			return (2);
		data->i = data->j + 1;
		return (1);
	}
	return (0);
}
