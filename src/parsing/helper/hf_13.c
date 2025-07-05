/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hf_13.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:14:55 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:30:01 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing	*handle_quote_space(t_lexer_data *data, t_parsing *head,
		t_env *envs)
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

t_parsing	*save_quote_content(t_lexer_data *data, t_parsing *head, char *tmp,
		t_env *envs)
{
	enum e_type	c;

	c = data->quote_type;
	if (c == 34)
		data->state = INDQUOTE;
	else
		data->state = INQUOTE;
	data->token_type = -1;
	data->char_value = 0;
	head = ft_save(data, head, envs, tmp);
	data->state = GENERAL;
	data->token_type = c;
	data->char_value = c;
	head = ft_save(data, head, envs, data->str);
	return (head);
}

t_parsing	*process_quote_content(t_lexer_data *data, t_parsing *head,
		t_env *envs)
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
			tmp[j] = '\0';
			head = save_quote_content(data, head, tmp, envs);
			break ;
		}
	}
	return (handle_quote_space(data, head, envs));
}
