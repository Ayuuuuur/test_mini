/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hf_11.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:23:47 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/04 18:29:06 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	setup_heredoc_signals(int *fds)
{
	signal(SIGINT, sig_heredoc);
	close(fds[0]);
}

char	*process_heredoc_line(char *line, int flag, t_env *envp)
{
	char	*expanded_line;

	if (flag == 0)
	{
		expanded_line = expand_var(line, envp, 0);
		free(line);
		line = expanded_line;
	}
	return (line);
}

void	write_line_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	heredoc_input_loop(int *fds, char *delimiter, int flag, t_env *envp)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		line = process_heredoc_line(line, flag, envp);
		if (!line)
		{
			error_msg_heredoc(delimiter);
			break ;
		}
		write_line_to_pipe(fds[1], line);
		free(line);
	}
}

void	run_heredoc(int *fds, t_parsing *head, int flag, t_env *envp)
{
	char	*delimiter;

	delimiter = build_delimiter(head, &flag, envp);
	setup_heredoc_signals(fds);
	heredoc_input_loop(fds, delimiter, flag, envp);
	close(fds[1]);
	exit(0);
}
