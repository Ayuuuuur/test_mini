/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:51:05 by nahilal           #+#    #+#             */
/*   Updated: 2025/04/29 18:54:15 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parsing *lexer(char *str, t_env *envs)
{
    t_parsing *head;
    char *tmp;
    enum e_state state;

    state = GENERAL;
    head = NULL;
    int i;
    int j;
    enum e_type c;
    int t;

    i = 0;
    j = 0;
    c = 0;
    int len = ft_strlen(str);
    while(str[i])
    {
        if(str[i] == ' ')
            head = ft_save(tmp,head,WHITE_SPACE,1,state, envs);
        while(str[i] == ' ')
            i++;
        state = GENERAL;
        c = check_token(str,i);
        if(c == ENV)
        {
            tmp = g_collector(len + 1, envs);
            j = 0;
            while(str[i])
            {
                c = check_token(str,i);
                if(c == WHITE_SPACE || c == PIPE_LINE ||c == DQUOTE || c == QUOTE || c == REDIR_OUT
                    || c == REDIR_IN || c == HERE_DOC || c == DREDIR_OUT)
                    break;
                tmp[j] = str[i];
                i++;
                j++;
            }
            tmp[j] = 0;
            state = ENV_STRING;
            head = ft_save(tmp,head,WORD,0,state, envs);
            if(str[i] == 0)
                break;
            continue;
        }
        if(c == DREDIR_OUT || c == HERE_DOC)
        {
            t = c;
            if(c == DREDIR_OUT)
                c = '>';
            else
                c = '<';
            tmp = g_collector(3, envs);
            tmp[0] = c;
            tmp[1] = c;
            tmp[2] = 0;
            head = ft_save(tmp,head,t,0,state, envs);
            i += 2;
            continue;
        }
        else if(c == -1)
        {
            t = c;
            tmp = g_collector(len + 1, envs);
            j = 0;
            while(c == -1 && str[i])
            {
                tmp[j++] = str[i++];
                c = check_token(str,i);
                if(c != -1 || str[i] == 0)
                {
                    tmp[j] = '\0';
                    head = ft_save(tmp,head,t,0,state, envs);
                    if(c != -1)
                        i--;
                    break;
                }
            }
            if(str[i] == 0)
                break;
            if(str[i + 1] == ' ')
            {
                head = ft_save(tmp,head,WHITE_SPACE,1,state, envs);
                i++;
            }
        }
        else if(c == 34 || c == 39)
        {
            head = ft_save(str,head,c,str[i],state, envs);
            i++;
            j = 0;
            tmp = g_collector(len + 1, envs);
            t = c;
            if(str[i] == c)
            {
                head = ft_save(str,head,c,str[i],state, envs);
                i++;
                continue;
            }
            while(str[i] && str[i] != t)
            {
                tmp[j++] = str[i++];
                c = check_token(str,i);
                if(c == t)
                {
                    if(c == 34)
                        state = INDQUOTE;
                    else
                        state = INQUOTE;
                    tmp[j] = '\0';
                    head = ft_save(tmp,head,-1,0,state, envs);
                    if(c == t)
                    {
                        state = GENERAL;
                        head = ft_save(str,head,c,c,state, envs);
                    } 
                    break;
                }
            }
            if(str[i] == 0)
                break;
            if(str[i + 1] == ' ')
            {
                head = ft_save(tmp,head,WHITE_SPACE,1,state, envs);
                i++;
            }
        }
        else
            head = ft_save(str,head,c,str[i],state, envs);
        i++;
    }
    
    return(head);
}
