/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:41:28 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:35:54 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum e_type	check_quote_tokens(char c)
{
	if (c == '\'')
		return (QUOTE);
	else if (c == '\"')
		return (DQUOTE);
	return (WORD);
}

enum e_type	check_whitespace_tokens(char c)
{
	if (c == ' ')
		return (WHITE_SPACE);
	else if (c == '\n')
		return (NEW_LINE);
	else if (c == '\0')
		return (NULL_TER);
	return (WORD);
}

enum e_type	check_special_tokens(char c)
{
	if (c == '\\')
		return (ESCAPE);
	else if (c == '$')
		return (ENV);
	else if (c == '|')
		return (PIPE_LINE);
	return (WORD);
}

enum e_type	check_redirect_tokens(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (DREDIR_OUT);
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (HERE_DOC);
		return (REDIR_IN);
	}
	else if (str[i] == '>')
		return (REDIR_OUT);
	return (WORD);
}

enum e_type	check_token(char *str, int i)
{
	enum e_type	result;

	result = check_quote_tokens(str[i]);
	if (result != WORD)
		return (result);
	result = check_whitespace_tokens(str[i]);
	if (result != WORD)
		return (result);
	result = check_special_tokens(str[i]);
	if (result != WORD)
		return (result);
	result = check_redirect_tokens(str, i);
	return (result);
}
