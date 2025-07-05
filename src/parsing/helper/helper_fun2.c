/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 02:13:10 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:36:24 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing	*handle_word_space(t_lexer_data *data, t_parsing *head, t_env *envs)
{
	if (data->str[data->i] == 0)
		return (head);
	if (data->str[data->i + 1] == ' ')
	{
		data->token_type = WHITE_SPACE;
		data->char_value = 1;
		head = ft_save(data, head, envs, NULL);
		data->i++;
	}
	return (head);
}

t_parsing	*handle_quote_token(t_lexer_data *data, t_parsing *head,
		t_env *envs)
{
	data->token_type = data->quote_type;
	data->char_value = data->str[data->i];
	head = ft_save(data, head, envs, data->str);
	data->i++;
	if (data->str[data->i] == data->quote_type)
	{
		data->token_type = data->quote_type;
		data->char_value = data->str[data->i];
		head = ft_save(data, head, envs, data->str);
		return (head);
	}
	return (process_quote_content(data, head, envs));
}

char	*build_word_content(t_lexer_data *data, t_env *envs)
{
	char		*tmp;
	int			j;
	enum e_type	c;

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
			if (c != -1)
				data->i--;
			break ;
		}
	}
	return (tmp);
}

t_parsing	*handle_word_token(t_lexer_data *data, t_parsing *head, t_env *envs)
{
	char	*tmp;

	tmp = build_word_content(data, envs);
	data->token_type = -1;
	data->char_value = 0;
	head = ft_save(data, head, envs, tmp);
	return (handle_word_space(data, head, envs));
}
