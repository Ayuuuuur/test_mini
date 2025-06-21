/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:46:25 by himousta          #+#    #+#             */
/*   Updated: 2025/04/28 21:10:55 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (!s || fd < 0)
		return ;
	ft_strlen(s);
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
