/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:46:23 by himousta          #+#    #+#             */
/*   Updated: 2025/07/04 03:02:22 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	g_exit_status = 1;
	return (EXIT_FAILURE);
}

int	ft_perror_cd(void)
{
	g_exit_status = 1;
	perror("minishell");
	return (EXIT_FAILURE);
}

int	ft_perror(char *err_msg, int len_cmd, int **pipes)
{
	perror(err_msg);
	close_pipes(len_cmd - 1, pipes);
	g_exit_status = 1;
	return (g_exit_status);
}

void	message_error_exit(char *str, int is_child, t_env *envs)
{
	display_exit(is_child);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	clean_memory(&(envs->head_gc));
	free_list(&(envs));
	exit(2);
}
