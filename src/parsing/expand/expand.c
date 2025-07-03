/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/06/22 12:00:00 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *ft_charjoin(char *str,char c, t_env *envp)
{
    int len;
    int i;
    char *s;

    if(!str)
        return(NULL);
    i = 0;
    len = ft_strlen(str);
    s = g_collector(len + 2, envp);
    while(str[i])
    {
        s[i] = str[i];
        i++;
    }
    s[i++] = c;
    s[i]= 0;
    return(s);
}

char *check_env_general(char *str, t_env *envp)
{
    int i;
    t_env *tmp;
    char *s;

    i = 0;
    tmp = envp;
    s = g_collector(2, envp);
    s[0] = 0;
    while(str[i] && str[i] == ' ')
        i++;
    i = 0;
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            if(str[i] == '?')
            {
                s = ft_strjoin(s,ft_itoa(G_EXIT_STATUS,envp),envp);
                i++;
                continue;
            }
            else if(str[i] == '$' || (str[i - 1] == '$' && str[i] == 0))
            {
                s = join_char(s,'$',envp);
                continue;
            }
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
                    s = ft_strjoin(s,tmp->value, envp);
                    
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
        s = ft_charjoin(s,str[i], envp);
        i++;
    }
    return(s);
}

int ft_split_expand(char **s1, t_var *data, t_env *envp)
{
    int i;
    i = 0;

    if(!s1)
        return(0);
    while(s1[i])
    {
        data->s[data->l] = ft_strdup(s1[i], envp);
        if(!data->s[data->l])
            return(0);
        data->l++;
        i++;
    }
    return(1);
}

int is_standalone_env_var(t_parsing *head)
{
    if (!head || head->state != 3)
        return 0;
    if (!head->next || head->next->type == WHITE_SPACE || 
        head->next->type == PIPE_LINE || head->next->type == REDIR_IN ||
        head->next->type == REDIR_OUT || head->next->type == HERE_DOC ||
        head->next->type == DREDIR_OUT)
        return 1;
    
    return 0;
}

int handle_env_split(t_parsing *head, t_env *envp, t_var *data)
{
    char *expanded_value;
    char **split_env;
    int i;
    expanded_value = check_env_general(head->content, envp);
    if (!expanded_value)
        return 0;
    if (ft_strchr(expanded_value, ' '))
    {
        split_env = ft_split(expanded_value, ' ', envp);
        if (!split_env)
        {
            // free(expanded_value);
            return 0;
        }
        i = 0;
        while (split_env[i])
        {
            if (ft_strlen(split_env[i]) > 0)
            {
                data->s[data->l] = ft_strdup(split_env[i], envp);
                if (!data->s[data->l])
                {
                    // free_2d(split_env);
                    // free(expanded_value);
                    return 0;
                }
                data->l++;
            }
            i++;
        }
        // free_2d(split_env);
        // free(expanded_value);
        return(1); 
    }
    else
    {
        if (ft_strlen(expanded_value) > 0)
        {
            data->s[data->l] = expanded_value;
            data->l++;
        }
        // else
        // {
            // free(expanded_value);
        // }
        return (1);
    }
}

char *get_token_value(t_parsing *head, t_env *envp, t_var *data)
{
    if (!head || !head->content)
        return ft_strdup("", envp);
    if (head->state == 3)
        return check_env_general(head->content, envp);
    else if (head->state == 2)
    {
        if (ft_double(head->content, envp, data) == 2)
            return NULL;
        if(data->s1)
            return(ft_strdup(data->s1, envp));
        else 
            return(ft_strdup("", envp));
    }
    else if (head->state == 1)
        return ft_strdup(head->content, envp);
    else if (head->state == 0 && head->type == WORD) 
        return ft_strdup(head->content, envp);
    return ft_strdup("", envp);
}

t_parsing *expand(t_parsing *head, t_env *envp, t_var *data, t_cmd **cmd)
{
    char *concatenated_value;
    char *temp_value;
    t_parsing *current;
    t_parsing *peek;
    char *new_concat;
    
    if(!head)
        return(NULL);  
    if(!head->content)
        return(head);     
    head = check_space(head);
    if(!head)
        return(NULL);
    if(head->type == PIPE_LINE)
    {
        *cmd = ft_send(data, *cmd, envp);
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
        int flag = 0;
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
        return(heredoce(head, data ,flag,envp));
    }
    
    if(head->type == DREDIR_OUT || head->type == REDIR_OUT) 
    {
        if(ft_redirect_out(head, data) == 2)
            return(NULL);
        head = head->next;
        head = check_space(head);
        return(head);
    }
    if (is_standalone_env_var(head))
    {
        if (!handle_env_split(head, envp, data))
            return NULL;
        return head;
    }
    if (head->type == DQUOTE || head->type == QUOTE || 
        head->type == WORD || head->state == 2 || head->state == 3)
    {
        concatenated_value = ft_strdup("", envp);
        current = head;
        
        if (current->type == DQUOTE || current->type == QUOTE)
            current = current->next;
        while (current && (current->type == WORD || current->state == 1 || 
                          current->state == 2 || current->state == 3 ||
                          current->type == DQUOTE || current->type == QUOTE ))
        {
            if (current->type == DQUOTE || current->type == QUOTE)
            {
                current = current->next;
                continue;
            }
            temp_value = get_token_value(current, envp, data);
            if (!temp_value)
            {
                // free(concatenated_value);
                return NULL;
            }
            
            new_concat = ft_strjoin(concatenated_value, temp_value, envp);
            // free(concatenated_value);
            // free(temp_value);
            
            if (!new_concat)
                return NULL;
            concatenated_value = new_concat;
            current = current->next;            
            if (current && (current->type == DQUOTE || current->type == QUOTE))
            {
                peek = current->next;
                if (peek && (peek->type == WORD || peek->state == 1 || 
                           peek->state == 2 || peek->state == 3))
                    continue;
                else
                    break;
            }
            if (current && (current->type == WHITE_SPACE || current->type == PIPE_LINE ||
                          current->type == REDIR_IN || current->type == REDIR_OUT ||
                          current->type == HERE_DOC || current->type == DREDIR_OUT))
                break;
        }
        if (concatenated_value && ft_strlen(concatenated_value) > 0)
        {
            data->s[data->l] = concatenated_value;
            data->l++;
        }
        // else
        // {
        //     free(concatenated_value);
        // }
        if(current && current->type == PIPE_LINE)
        {
            *cmd = ft_send(data, *cmd, envp);
            data->l = 0;
            data->in_file = -1;
            data->out_file = -1;
            return(current);
        }
        if (current)
            return current;
        else
            return head;
    }
    
    return(head);
}