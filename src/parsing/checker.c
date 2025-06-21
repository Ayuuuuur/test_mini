/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:42:31 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/06 18:42:55 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int  checker(t_parsing *head,t_env *envp, int len,t_cmd **cmd)
{
    if(syntax_err(head) == 2)
        return(2);
    if(check_expand(head,envp,len,cmd) == 2)
        return(2);    
    return(1);
}