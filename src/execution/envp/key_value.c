/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:21:28 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:21:28 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**creat_mini_envp(void)
{
	char	**minimal_envp;

	minimal_envp = malloc(sizeof(char *) * 5);
	minimal_envp[0] = ft_strdup_env("PATH=/usr/local/sbin:\
		/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	minimal_envp[1] = ft_strdup_env("OLDPWD");
	minimal_envp[2] = get_pwd();
	minimal_envp[3] = ft_strdup_env("SHLVL=1");
	minimal_envp[4] = NULL;
	return (minimal_envp);
}

t_env	*split_key_value(int is_exported, char *env, t_env *n_node, char **envp)
{
	char	*value;
	char	**key;

	value = ft_strchr(env, '=');
	key = ft_split_env(env, '=');
	if (!key)
		return (NULL);
	n_node->key = ft_strdup_env(key[0]);
	free_2d(key);
	n_node->value = ft_strdup_env(value + 1);
	n_node->next = 0;
	n_node->head_gc = NULL;
	if (ft_strcmp(n_node->key, "PATH") == 0
		&& (!envp || !envp[0]) && !is_exported)
	{
		n_node->flag_exported = 2;
		is_exported = 1;
	}
	else
		n_node->flag_exported = 1;
	return (n_node);
}

t_env	*new_env(char *env, char **envp)
{
	static int	is_path_exported;
	t_env		*newnode;

	newnode = (t_env *)malloc(sizeof(t_env));
	if (!newnode)
		return (NULL);
	if (ft_strchr(env, '=') != NULL)
		newnode = split_key_value(is_path_exported, env, newnode, envp);
	else
	{
		newnode->key = ft_strdup_env(env);
		newnode->value = NULL;
		newnode->flag_exported = 0;
		newnode->next = 0;
		newnode->head_gc = NULL;
	}
	return (newnode);
}

void	add_env(t_env *newnode, t_env **head_list)
{
	t_env	*temp;

	temp = (*head_list);
	if (temp == 0)
		(*head_list) = newnode;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = newnode;
	}
}

char	*get_pwd(void)
{
	char	*working_d;
	char	*complet_pwd;

	working_d = getcwd(NULL, 0);
	if (!working_d)
	{
		perror("minishell");
		return (NULL);
	}
	complet_pwd = ft_strjoin_env("PWD=", working_d);
	free(working_d);
	return (complet_pwd);
}
