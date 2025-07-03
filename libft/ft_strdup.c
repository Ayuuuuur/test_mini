/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:50:30 by himousta          #+#    #+#             */
/*   Updated: 2024/11/15 10:26:22 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1, t_env *envs)
{
	char			*str;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = (char *)g_collector((len + 1) * sizeof(char), envs);
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
