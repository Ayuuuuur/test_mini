/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:52:57 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 22:53:29 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_flag_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int (i), (check);
	i = 1;
	check = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && check_flag_n(args[i]) == 1)
			check = 1;
		else
			break ;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (check == 0)
		printf("\n");
	g_exit_status = 0;
	return (EXIT_SUCCESS);
}
