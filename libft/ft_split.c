/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:34:05 by himousta          #+#    #+#             */
/*   Updated: 2024/11/15 10:26:11 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_word(char const *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == c) && (str[i] != c))
			count++;
		i++;
	}
	return (count);
}

static int	wordlen(const char *str, char c)
{
	int	start;

	start = 0;
	while (str[start] != c && str[start] != '\0')
		start++;
	return (start);
}

static char	*ft_stdup(const char *src, int len, t_env *envs)
{
	char	*str;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	str = (char *)g_collector((len + 1) * sizeof(char), envs);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c, t_env *envs)
{
	char	**str;

	int (i), (j);
	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = (char **)g_collector((count_word(s, c) + 1) * sizeof(char *), envs);
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			str[j++] = ft_stdup((s + i), wordlen((s + i), c), envs);
			if (!str[j - 1])
			{
				return (NULL);
			}
			i += wordlen((s + i), c);
		}
	}
	return (str[j] = NULL, str);
}
