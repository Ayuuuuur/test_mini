/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:57:21 by himousta          #+#    #+#             */
/*   Updated: 2024/11/15 10:21:50 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	len_numbre(long int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n, t_env *envs)
{
	char		*str;
	size_t		len;
	long int	nb;

	nb = n;
	str = (char *)g_collector(((len = len_numbre(nb)) + 1) * sizeof(char), envs);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	else
	{
		while (len > 0 && nb > 0)
		{
			str[--len] = ((nb % 10) + 48);
			nb /= 10;
		}
	}
	return (str);
}
