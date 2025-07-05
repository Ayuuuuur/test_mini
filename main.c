/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/07/05 19:42:43 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <readline/history.h>

int		g_exit_status = 0;

int	lexer_checker(char *rdl, t_env *envs, t_cmd **cmd)
{
	t_parsing	*head;

	head = lexer(rdl, envs);
	if (checker(head, envs, ft_strlen(rdl), cmd) == 2)
	{
		free(rdl);
		return (0);
	}
	return (1);
}

char	*read_line(t_env *envs, char *rdl)
{
	rdl = readline(shell_prompt(envs));
	if (!rdl)
	{
		printf("exit\n");
		clean_memory(&(envs->head_gc));
		free_list(&envs);
		exit(g_exit_status);
	}
	return (rdl);
}

int	send_to_execution(t_cmd *cmd, t_env *envs, int *arr_in_out, char *rdl)
{
	t_cmd	*commads_in_out;
	t_pids	*pids;

	commads_in_out = cmd;
	if (commads_in_out)
	{
		pids = execute_commands(&envs, commads_in_out);
		if (!pids)
			return (0);
		restore_stdin_out(arr_in_out);
		waiting_childs(pids);
	}
	free(rdl);
	cmd = NULL;
	clean_memory(&(envs->head_gc));
	return (1);
}

int	main_loop(t_env *envs, char *rdl)
{
	int		*arr_in_out;
	t_cmd	*cmd;

	cmd = NULL;
	arr_in_out = save_in_out(envs);
	rdl = read_line(envs, rdl);
	if (space_skip_main(rdl) == 0)
		return (1);
	if (lexer_checker(rdl, envs, &cmd) == 0)
		return (1);
	if (send_to_execution(cmd, envs, arr_in_out, rdl) == 0)
		return (0);
	return (2);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*envs;
	int		i;
	char	*rdl;

	(void)ac;
	(void)av;
	rdl = NULL;
	signal(SIGQUIT, SIG_IGN);
	if (env_main(&envs, envp) == 1)
		return (1);
	envs->head_gc = NULL;
	while (1)
	{
		signal(SIGINT, my_handller);
		i = main_loop(envs, rdl);
		if (i == 1)
			continue ;
		if (i == 0)
			return (0);
		free(rdl);
	}
	return (0);
}
