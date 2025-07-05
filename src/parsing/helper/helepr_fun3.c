/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helepr_fun3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:26:07 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:25:41 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_charjoin(char *str, char c, t_env *envp)
{
	int		len;
	int		i;
	char	*s;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	s = g_collector(len + 2, envp);
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = c;
	s[i] = 0;
	return (s);
}

int	check_help_env(int *i, char *str)
{
	if (ft_isalnum(str[*i]) == 1)
	{
		(*i)++;
		while (str[*i] && str[*i] != ' ')
		{
			if (str[*i] == ' ')
				return (1);
			(*i)++;
		}
		while (str[*i] && str[*i] == ' ')
			(*i)++;
		return (1);
	}
	return (0);
}

char	*process_env_variable(char *str, int *i, t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, str + *i, ft_strlen(tmp->key)) == 0)
		{
			*i += ft_strlen(tmp->key);
			if (check_help_env(i, str) == 1)
				break ;
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*handle_special_dollar(char *str, int *i, t_env *envp, char *s)
{
	if (str[*i] == '?')
	{
		s = ft_strjoin(s, ft_itoa(g_exit_status, envp), envp);
		(*i)++;
		return (s);
	}
	else if (str[*i] == '$' || (str[*i - 1] == '$' && str[*i] == 0))
		return (join_char(s, '$', envp));
	return (NULL);
}

char	*handle_env_variable(char *str, int *i, t_env *envp, char *s)
{
	char	*env_value;

	env_value = process_env_variable(str, i, envp);
	if (env_value)
		s = ft_strjoin(s, env_value, envp);
	else
	{
		while (str[*i])
		{
			if (str[*i] == ' ' || ft_isalnum(str[*i]) == 0)
				break ;
			(*i)++;
		}
		while (str[*i] && str[*i] == ' ')
			(*i)++;
	}
	return (s);
}
