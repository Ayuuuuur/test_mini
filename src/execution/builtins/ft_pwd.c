/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:13:40 by hind              #+#    #+#             */
/*   Updated: 2025/07/04 03:03:32 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_pwd(t_env *envs)
{
	char	*working_d;
	int		should_free;

	working_d = getcwd(NULL, 0);
	if (working_d == NULL)
	{
		working_d = get_env_value("PWD", envs);
		if (!working_d)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		should_free = 0;
	}
	else
		should_free = 1;
	printf("%s\n", working_d);
	if (should_free == 1)
		free(working_d);
	g_exit_status = 0;
	return (EXIT_SUCCESS);
}
