/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 02:13:10 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 02:13:40 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing	*handle_quote_space(t_lexer_data *data, t_parsing *head
	, t_env *envs)
{
	char	*tmp;

	tmp = NULL;
	if (data->str[data->i] == 0)
		return (head);
	if (data->str[data->i + 1] == ' ')
	{
		head = ft_save(tmp, head, WHITE_SPACE, 1, data->state, envs);
		data->i++;
	}
	return (head);
}

t_parsing	*process_quote_content(t_lexer_data *data, t_parsing *head
	, t_env *envs)
{
	char		*tmp;
	int			j;
	enum e_type	c;

	j = 0;
	tmp = g_collector(data->len + 1, envs);
	while (data->str[data->i] && data->str[data->i] != data->quote_type)
	{
		tmp[j++] = data->str[data->i++];
		c = check_token(data->str, data->i);
		if (c == data->quote_type)
		{
			if (c == 34)
				data->state = INDQUOTE;
			else
				data->state = INQUOTE;
			tmp[j] = '\0';
			head = ft_save(tmp, head, -1, 0, data->state, envs);
			data->state = GENERAL;
			head = ft_save(data->str, head, c, c, data->state, envs);
			break ;
		}
	}
	return (handle_quote_space(data, head, envs));
}

t_parsing	*handle_word_space(t_lexer_data *data, t_parsing *head, t_env *envs)
{
	char	*tmp;

	tmp = NULL;
	if (data->str[data->i] == 0)
		return (head);
	if (data->str[data->i + 1] == ' ')
	{
		head = ft_save(tmp, head, WHITE_SPACE, 1, data->state, envs);
		data->i++;
	}
	return (head);
}

t_parsing	*handle_quote_token(t_lexer_data *data, t_parsing *head
	, t_env *envs)
{
	head = ft_save(data->str, head, data->quote_type, data->str[data->i],
			data->state, envs);
	data->i++;
	if (data->str[data->i] == data->quote_type)
	{
		head = ft_save(data->str, head, data->quote_type,
				data->str[data->i], data->state, envs);
		data->i++;
		data->i--;
		return (head);
	}
	return (process_quote_content(data, head, envs));
}

t_parsing	*handle_word_token(t_lexer_data *data, t_parsing *head
	, t_env *envs)
{
	char		*tmp;
	int			j;
	enum e_type	c;
	int			t;

	t = -1;
	tmp = g_collector(data->len + 1, envs);
	j = 0;
	c = -1;
	while (c == -1 && data->str[data->i])
	{
		tmp[j++] = data->str[data->i++];
		c = check_token(data->str, data->i);
		if (c != -1 || data->str[data->i] == 0)
		{
			tmp[j] = '\0';
			head = ft_save(tmp, head, t, 0, data->state, envs);
			if (c != -1)
				data->i--;
			break ;
		}
	}
	return (handle_word_space(data, head, envs));
}