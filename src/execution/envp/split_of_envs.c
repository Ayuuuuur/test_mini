/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_of_envs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:29:56 by hind              #+#    #+#             */
/*   Updated: 2025/07/03 23:30:27 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static char	*ft_stdup(const char *src, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	str = (char *)malloc((len + 1) * sizeof(char));
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

static void	free_split(char **arr, int arrlen)
{
	while (arrlen >= 0)
	{
		free(arr[arrlen]);
		arrlen--;
	}
	free(arr);
}

char	**ft_split_env(char const *s, char c)
{
	char	**str;

	int (i), (j);
	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			str[j++] = ft_stdup((s + i), wordlen((s + i), c));
			if (!str[j - 1])
			{
				return (free_split(str, j - 1), NULL);
			}
			i += wordlen((s + i), c);
		}
	}
	return (str[j] = NULL, str);
}
