/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:51:05 by nahilal           #+#    #+#             */
/*   Updated: 2025/04/29 18:54:15 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing	*handle_double_redirect(t_lexer_data *data, t_parsing *head
	, t_env *envs)
{
	char		*tmp;
	int			t;
	enum e_type	c;

	c = data->redirect_type;
	t = c;
	if (c == DREDIR_OUT)
		c = '>';
	else
		c = '<';
	tmp = g_collector(3, envs);
	tmp[0] = c;
	tmp[1] = c;
	tmp[2] = 0;
	head = ft_save(tmp, head, t, 0, data->state, envs);
	data->i += 2;
	data->i--;
	return (head);
}

t_parsing	*handle_env_token(t_lexer_data *data, t_parsing *head
	, t_env *envs)
{
	char		*tmp;
	int			j;
	enum e_type	c;

	tmp = g_collector(data->len + 1, envs);
	j = 0;
	while (data->str[data->i])
	{
		c = check_token(data->str, data->i);
		if (c == WHITE_SPACE || c == PIPE_LINE || c == DQUOTE || c == QUOTE
			|| c == REDIR_OUT || c == REDIR_IN || c == HERE_DOC
			|| c == DREDIR_OUT)
			break ;
		tmp[j] = data->str[data->i];
		data->i++;
		j++;
	}
	tmp[j] = 0;
	data->state = ENV_STRING;
	head = ft_save(tmp, head, WORD, 0, data->state, envs);
	data->i--;
	return (head);
}

t_parsing	*handle_spaces(t_lexer_data *data, t_parsing *head, t_env *envs)
{
	char	*tmp;

	tmp = NULL;
	if (data->str[data->i] == ' ')
		head = ft_save(tmp, head, WHITE_SPACE, 1, data->state, envs);
	while (data->str[data->i] == ' ')
		data->i++;
	data->state = GENERAL;
	return (head);
}

t_parsing	*process_token(t_lexer_data *data, t_parsing *head, t_env *envs)
{
	enum e_type	c;

	c = check_token(data->str, data->i);
	if (c == ENV)
		return (handle_env_token(data, head, envs));
	else if (c == DREDIR_OUT || c == HERE_DOC)
	{
		data->redirect_type = c;
		return (handle_double_redirect(data, head, envs));
	}
	else if (c == -1)
		return (handle_word_token(data, head, envs));
	else if (c == 34 || c == 39)
	{
		data->quote_type = c;
		return (handle_quote_token(data, head, envs));
	}
	else
		return (ft_save(data->str, head, c, data->str[data->i]
				, data->state, envs));
}

t_parsing	*lexer(char *str, t_env *envs)
{
	t_parsing		*head;
	t_lexer_data	data;

	head = NULL;
	data.str = str;
	data.i = 0;
	data.len = ft_strlen(str);
	data.state = GENERAL;
	while (data.str[data.i])
	{
		head = handle_spaces(&data, head, envs);
		head = process_token(&data, head, envs);
		if (data.str[data.i] == 0)
			break ;
		data.i++;
	}
	return (head);
}
