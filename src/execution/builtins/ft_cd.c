/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:52:44 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 22:52:44 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	set_env(char *var, char *new_value, t_env *envs)
{
	while (envs)
	{
		if (ft_strcmp(var, envs->key) == 0 && new_value)
		{
			if (envs->value)
				free(envs->value);
			envs->value = ft_strdup_env(new_value);
			envs->flag_exported = 1;
			return (0);
		}
		envs = envs->next;
	}
	return (1);
}

char	*get_env_value(char *key, t_env *envs)
{
	if (!key || !envs)
		return (NULL);
	while (envs)
	{
		if (ft_strcmp(key, envs->key) == 0)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

int	go_new_dir(char *new_dir, t_env *envs, char *oldpwd)
{
	char	*pwd;

	if (new_dir == NULL || ft_strcmp(new_dir, "~") == 0)
	{
		if (chdir(get_env_value("HOME", envs)) == -1)
			return (print_error("minishell: cd: HOME not set\n"));
	}
	else if (strcmp(new_dir, "-") == 0)
	{
		if (chdir(get_env_value("OLDPWD", envs)) == -1)
			return (print_error("minishill: cd: OLDPWD not set\n"));
		printf("%s\n", get_env_value("OLDPWD", envs));
	}
	else if (chdir(new_dir) == -1)
		return (ft_perror_cd());
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_perror_cd());
	set_env("OLDPWD", oldpwd, envs);
	set_env("PWD", pwd, envs);
	free(pwd);
	g_exit_status = 0;
	return (EXIT_SUCCESS);
}

int	ft_cd(char **args, t_env *envs)
{
	char	*oldpwd;
	char	*allocated_oldpwd;
	int		i;
	int		result;

	i = 0;
	allocated_oldpwd = NULL;
	while (args[i] != NULL)
		i++;
	if (i > 2)
		return (print_error("minishell: cd: too many arguments\n"));
	oldpwd = get_env_value("PWD", envs);
	if (oldpwd == NULL)
	{
		allocated_oldpwd = getcwd(NULL, 0);
		oldpwd = allocated_oldpwd;
	}
	result = go_new_dir(args[1], envs, oldpwd);
	if (allocated_oldpwd)
		free(allocated_oldpwd);
	return (result);
}
