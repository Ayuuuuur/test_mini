/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:02:05 by marvin            #+#    #+#             */
/*   Updated: 2025/07/04 18:36:13 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	closing(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

void	error_msg_heredoc(char *delimiter)
{
	ft_putstr_fd("minishell: warning: line delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("`)\n", 2);
}

int	wait_heredoc(t_var *data, int pid, int *fds)
{
	int	state;

	sig_ignore();
	waitpid(pid, &state, 0);
	close(fds[1]);
	if (WIFEXITED(state))
	{
		g_exit_status = WEXITSTATUS(state);
		if (g_exit_status == 130)
		{
			close(fds[0]);
			return (2);
		}
	}
	data->in_file = fds[0];
	return (0);
}

t_parsing	*skip_delimiter(t_parsing *head)
{
	if (!head->next)
		return (head);
	head = head->next;
	while (head)
	{
		if (!head->next || (head->next && head->next->type == PIPE_LINE)
			|| head->type == PIPE_LINE || head->type == SPACE)
			break ;
		head = head->next;
	}
	return (head);
}

t_parsing	*heredoce(t_parsing *head, t_var *data, int flag, t_env *envp)
{
	int	*fds;
	int	pid;

	fds = g_collector(2 * sizeof(int), envp);
	if (pipe(fds) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (closing(fds), NULL);
	if (pid == 0)
		run_heredoc(fds, head, flag, envp);
	else
	{
		if (wait_heredoc(data, pid, fds) == 2)
			return (NULL);
	}
	head = skip_delimiter(head);
	return (head);
}
