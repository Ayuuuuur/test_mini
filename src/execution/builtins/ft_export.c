/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:06:47 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:13:16 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exist_env(t_env *newnode, t_env *temp_env)
{
	while (temp_env)
	{
		if (ft_strcmp(temp_env->key, newnode->key) == 0
			&& temp_env->flag_exported == 1 && newnode->value == NULL)
			return (0);
		if (ft_strcmp(temp_env->key, newnode->key) == 0)
		{
			if (temp_env->value != NULL)
				free(temp_env->value);
			temp_env->value = ft_strdup(newnode->value, temp_env);
			temp_env->flag_exported = newnode->flag_exported;
			return (0);
		}
		temp_env = temp_env->next;
	}
	return (1);
}

void	print_env_list(t_env *head)
{
	while (head)
	{
		if (head->flag_exported == 2)
		{
			if (!head->next)
				return ;
			head = head->next;
		}
		if (head->flag_exported == 1)
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		else
			printf("declare -x %s\n", head->key);
		head = head->next;
	}
	return ;
}

int	valide_name(char *str)
{
	int	i;

	i = 0;
	if ((str[i] < 'a' || str[i] > 'z')
		&& (str[i] < 'A' || str[i] > 'Z')
		&& str[i] != '_')
		return (-1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] < 'a' || str[i] > 'z')
			&& (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9')
			&& str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	message_error_export(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

int	ft_export(char **args, t_env **envs)
{
	t_env	*newnode;
	int		i;

	i = 1;
	while (args[i])
	{
		if (valide_name(args[i]) == -1)
			message_error_export(args[i]);
		else
		{
			newnode = new_env(args[i], NULL);
			if (exist_env(newnode, (*envs)) == 0)
				free_node(newnode);
			else
				add_env(newnode, envs);
		}
		i++;
	}
	if (i == 1)
		print_env_list(*envs);
	return (EXIT_SUCCESS);
}
