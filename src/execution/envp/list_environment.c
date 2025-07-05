/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:28:21 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:29:51 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (i < len && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_env(const char *s1)
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_env	*list_envs(char **envp)
{
	char	**minimal_envp;

	if (!envp)
		return (NULL);
	else if (envp[0] == NULL)
	{
		minimal_envp = creat_mini_envp();
		return (build_new_envs(minimal_envp, envp, 'm'));
	}
	else
		return (build_new_envs(envp, envp, 'o'));
}

t_env	*build_new_envs(char **envs, char **envp, char flag)
{
	t_env	*head_env;
	t_env	*newnode;
	int		i;

	head_env = 0;
	i = 0;
	while (envs[i])
	{
		newnode = new_env(envs[i], envp);
		if (!newnode)
		{
			free_list(&head_env);
			return (NULL);
		}
		add_env(newnode, &head_env);
		i++;
	}
	if (flag == 'm')
		free_2d(envs);
	return (head_env);
}
