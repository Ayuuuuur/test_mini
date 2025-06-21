/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:21:44 by himousta          #+#    #+#             */
/*   Updated: 2024/11/15 10:26:39 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	size_t			lendst;
	size_t			lentotal;

	i = 0;
	if (!src && !dst)
		return (0);
	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	lendst = ft_strlen(dst);
	lentotal = lendst + ft_strlen(src);
	while (lendst < dstsize - 1 && src[i] && dstsize != 0)
	{
		dst[lendst++] = src[i++];
	}
	dst[lendst] = '\0';
	return (lentotal);
}
