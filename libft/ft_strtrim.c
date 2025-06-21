/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:40:54 by himousta          #+#    #+#             */
/*   Updated: 2024/11/14 20:29:06 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	search_char(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && (search_char(set, s1[i])))
		i++;
	len = ft_strlen(s1);
	while ((len > 0) && (search_char(set, s1[len - 1])))
		len--;
	if (len == 0)
	{
		str = (char *)malloc(1);
		if (str != NULL)
			str[0] = '\0';
		else
			return (NULL);
	}
	else
		str = ft_substr (s1, i, (len - i));
	return (str);
}
