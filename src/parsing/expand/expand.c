/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/05/06 18:51:16 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *ft_charjoin(char *str,char c)
{
    int len;
    int i;
    char *s;

    if(!str)
        return(NULL);
    i = 0;
    len = ft_strlen(str);
    s = malloc(len + 2);
    while(str[i])
    {
        s[i] = str[i];
        i++;
    }
    s[i++] = c;
    s[i]= 0;
    return(s);
}
int check_odd(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != '$')
            break;
        i++;
    }
    return(i);
}
char *check_env_general(char *str, t_env *envp, t_var *data)
{
    int i;
    int len;
    t_env *tmp;
    (void)data;
    char *s;

    i = 0;
    len = 0;
    tmp = envp;
    s = malloc(2);
    s[0] = 0;
    len = check_odd(str);
    if(len % 2 == 1)
        len--;
    while(str[i] && str[i] == ' ')
        i++;
    i += len;
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            tmp = envp;
            while(tmp)
            {
                if(ft_strncmp(tmp->key,str + i,ft_strlen(tmp->key)) == 0)
                {
                    i+= ft_strlen(tmp->key);
                    if(ft_isalnum(str[i]) == 1)
                    {
                        i++;
                        while(str[i] && str[i] != ' ')
                        {
                            if(str[i] == ' ')
                                break;
                            i++;
                        }
                        while(str[i] && str[i] == ' ')
                            i++;
                        break;
                    }
                    s = ft_strjoin(s,tmp->value);
                    break;
                }
                tmp = tmp->next;
            }
            if(!tmp)
            {
                while(str[i])
                {
                    if(str[i] == ' ' || ft_isalnum(str[i]) == 0)
                        break;
                    i++;
                }
                while(str[i]&& str[i] == ' ')
                    i++;
            }
            continue;
        }
        s = ft_charjoin(s,str[i]);
        i++;
    }
    return(s);
}

int ft_split_expand(char **s1, t_var *data)
{
    int i;
    i = 0;

    if(!s1)
        return(0);
    while(s1[i])
    {
        data->s[data->l] = ft_strdup(s1[i]);
        if(!data->s[data->l])
            return(0);
        data->l++;
        i++;
    }
    return(1);
}

t_parsing *expand(t_parsing *head, t_env *envp, t_var *data, t_cmd **cmd)
{
    int flag;

    if(!head)
        return(NULL);
    head = check_space(head);
    if(head->type == PIPE_LINE)
    {
        *cmd = ft_send(data, *cmd);
        data->l = 0;
        data->in_file = -1;
        data->out_file = -1;
        return(head);
    }
    
    if(head->type == REDIR_IN)
    {
        if(ft_redirect_in(head, data) == 2)
        return(NULL);
        head = head->next;
        head = check_space(head);
        return(head);
    }
    
    if(head->type == HERE_DOC)
    {
        flag = 0;
        head = head->next;
        if(!head)
            return(NULL);
        if(head->type == WHITE_SPACE)
            head = head->next;
        if(head->type == DQUOTE || head->type == QUOTE)
        {
            flag = 1;
            head = head->next;
        }   
        if(heredoce(head->content, data ,flag,envp) == 2)
            return(NULL);
        return(head);
    }
    
    if(head->type == DREDIR_OUT || head->type == REDIR_OUT) 
    {
        if(ft_redirect_out(head, data) == 2)
            return(NULL);
        head = head->next;
        head = check_space(head);
        printf("head->typ %s\n",head->content);
        return(head);
    }
    
    if(head->state == 3)
    {
        data->s[data->l] = check_env_general(head->content,envp,data);
        data->l++;
        if(!head->content)
            return(NULL);
        return(head);
    }
    if(head->state == 0 && head->type != DQUOTE && head->type != QUOTE)
    {
        
        data->s[data->l] = ft_strdup(head->content);
        data->l++;
        return(head);
    }
    if(head->state == 2)
    {
        printf("state 3\n");
        if(ft_double(head->content, envp, data) == 2)
            return(NULL);
        data->s[data->l] = ft_strdup(data->s1);
        data->l++;
        return(head);
    }
    
    if(head->state == 1)
    {
        printf("state 4\n");
        data->s[data->l] = ft_strdup(head->content);
        data->l++;
        return(head);
    }
    
    return(head);
}
