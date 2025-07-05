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

t_parsing	*handle_double_redirect(t_lexer_data *data, t_parsing *head,
		t_env *envs)
{
	char	*tmp;
	char	c;

	if (data->redirect_type == DREDIR_OUT)
		c = '>';
	else
		c = '<';
	tmp = g_collector(3, envs);
	tmp[0] = c;
	tmp[1] = c;
	tmp[2] = 0;
	data->token_type = data->redirect_type;
	data->char_value = 0;
	head = ft_save(data, head, envs, tmp);
	data->i += 2;
	data->i--;
	return (head);
}

t_parsing	*handle_env_token(t_lexer_data *data, t_parsing *head, t_env *envs)
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
	data->token_type = WORD;
	data->char_value = 0;
	head = ft_save(data, head, envs, tmp);
	data->i--;
	return (head);
}

t_parsing	*handle_spaces(t_lexer_data *data, t_parsing *head, t_env *envs)
{
	if (data->str[data->i] == ' ')
	{
		data->token_type = WHITE_SPACE;
		data->char_value = 1;
		head = ft_save(data, head, envs, NULL);
	}
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
	{
		data->token_type = c;
		data->char_value = data->str[data->i];
		return (ft_save(data, head, envs, data->str));
	}
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
