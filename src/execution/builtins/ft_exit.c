/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:01:10 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:01:10 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

long double	ft_atold(const char *str)
{
	long double	result;

	int (i), (sign), (check);
	i = 0;
	result = 0;
	sign = 1;
	check = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		check++;
	}
	return (result * sign);
}

int	is_valid_exit(char *arg)
{
	long double	re;
	int			i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (-1);
	while (arg[i])
	{
		if ((arg[i] < '0' || arg[i] > '9'))
			return (-1);
		i++;
	}
	re = ft_atold(arg);
	if (re < LLONG_MIN || re > LLONG_MAX)
		return (-1);
	return (0);
}

void	display_exit(int is_child)
{
	if (is_child != 1)
		ft_putstr_fd("exit\n", 2);
}

void	exit_and_clean(t_env *envs)
{
	clean_memory(&(envs->head_gc));
	free_list(&(envs));
	exit(g_exit_status % 256);
}

void	ft_exit(char **args, int is_child, t_env *envs)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
	{
		display_exit(is_child);
		exit_and_clean(envs);
	}
	else if (is_valid_exit(args[1]) == -1)
		message_error_exit(args[1], is_child, envs);
	else if (i > 2)
	{
		display_exit(is_child);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	else
	{
		display_exit(is_child);
		g_exit_status = ft_atoi(args[1]);
		exit_and_clean(envs);
	}
}
