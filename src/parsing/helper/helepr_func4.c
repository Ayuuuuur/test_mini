/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helepr_func4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:27:24 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:38:46 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*handle_dollar_sign(char *str, int *i, t_env *envp, char *s)
{
	char	*result;

	(*i)++;
	result = handle_special_dollar(str, i, envp, s);
	if (result)
		return (result);
	return (handle_env_variable(str, i, envp, s));
}

char	*check_env_general(char *str, t_env *envp)
{
	int		i;
	char	*s;

	i = 0;
	s = g_collector(2, envp);
	s[0] = 0;
	while (str[i] && str[i] == ' ')
		i++;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			s = handle_dollar_sign(str, &i, envp, s);
		else
		{
			s = ft_charjoin(s, str[i], envp);
			i++;
		}
	}
	return (s);
}

int	ft_split_expand(char **s1, t_var *data, t_env *envp)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		data->s[data->l] = ft_strdup(s1[i], envp);
		if (!data->s[data->l])
			return (0);
		data->l++;
		i++;
	}
	return (1);
}

int	is_standalone_env_var(t_parsing *head)
{
	if (!head || head->state != 3)
		return (0);
	if (!head->next || head->next->type == WHITE_SPACE
		|| head->next->type == PIPE_LINE || head->next->type == REDIR_IN
		|| head->next->type == REDIR_OUT || head->next->type == HERE_DOC
		|| head->next->type == DREDIR_OUT)
		return (1);
	return (0);
}

int	add_split_tokens(char **split_env, t_var *data, t_env *envp)
{
	int	i;

	i = 0;
	while (split_env[i])
	{
		if (ft_strlen(split_env[i]) > 0)
		{
			data->s[data->l] = ft_strdup(split_env[i], envp);
			if (!data->s[data->l])
				return (0);
			data->l++;
		}
		i++;
	}
	return (1);
}
