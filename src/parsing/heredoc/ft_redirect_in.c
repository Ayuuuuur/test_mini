/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:33:03 by marvin            #+#    #+#             */
/*   Updated: 2025/05/23 17:33:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_redirect_in(t_parsing *head , t_var *data)
{
    int fd;

    head = head->next;
    if(!head)
        return(2);
    head = check_space(head);
    fd = open(head->content,O_RDONLY);
    if(fd < 0)
    {
        perror("minishell");
        return(2);
    }
    data->in_file = fd;
    return(0);
}