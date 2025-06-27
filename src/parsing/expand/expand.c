/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:31:13 by nahilal           #+#    #+#             */
/*   Updated: 2025/06/27 22:23:18 by nahilal          ###   ########.fr       */
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

// Function removed - ! handling should be in execution phase

char *check_env_general(char *str, t_env *envp)
{
    int i;
    int len;
    t_env *tmp;
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

// Function to check if env variable should be split (standalone env var)
int should_split_env(t_parsing *token, t_parsing *next_token)
{
    // Only split if it's a standalone environment variable
    // (not concatenated with other tokens)
    if (token->state == 3 && (!next_token || 
        next_token->type == WHITE_SPACE || 
        next_token->type == PIPE_LINE ||
        next_token->type == REDIR_IN || 
        next_token->type == REDIR_OUT ||
        next_token->type == HERE_DOC || 
        next_token->type == DREDIR_OUT))
        return 1;
    return 0;
}

// New function to get concatenated token value
char *get_token_value(t_parsing *token, t_env *envp, t_var *data, char ***split_env, int *should_split)
{
    char *str;

    if (!token || !token->content)
        return ft_strdup("");
    
    if (token->state == 3) // ENV_STRING
    {
        str = check_env_general(token->content, envp);
        
        // Check if this env var should be split and contains spaces
        if (*should_split && str && ft_strchr(str, ' '))
        {
            *split_env = ft_split(str, ' ');
        }
        
        return str;
    }
    else if (token->state == 2) // INDQUOTE
    {
        if (ft_double(token->content, envp, data) == 2)
            return NULL;
        return ft_strdup(data->s1 ? data->s1 : "");
    }
    else if (token->state == 1) // INQUOTE
        return ft_strdup(token->content);
    else if (token->state == 0 && token->type == WORD) // GENERAL WORD
    {
        return ft_strdup(token->content);
    }
    
    return ft_strdup("");
}

t_parsing *expand(t_parsing *head, t_env *envp, t_var *data, t_cmd **cmd)
{
    char *concatenated_value;
    char *temp_value;
    t_parsing *current;
    char **split_env;
    int should_split;
    
    if(!head)
        return(NULL);
    
    // Skip tokens with NULL content (tokens that were marked for skipping)
    if(!head->content)
        return(head->next);
        
    head = check_space(head);
    if(!head)
        return(NULL);
        
    if(head->type == PIPE_LINE)
    {
        *cmd = ft_send(data, *cmd);
        data->l = 0;
        data->in_file = -1;
        data->out_file = -1;
        return(head->next);
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
        if(heredoce(head->content, data ,flag,envp) == 2)
            return(NULL);
        return(head->next);
    }
    
    if(head->type == DREDIR_OUT || head->type == REDIR_OUT) 
    {
        if(ft_redirect_out(head, data) == 2)
            return(NULL);
        head = head->next;
        head = check_space(head);
        return(head);
    }
    
    // Handle ONLY quotes and concatenation scenarios
    if (head->type == DQUOTE || head->type == QUOTE)
    {
        concatenated_value = ft_strdup("");
        current = head->next; // Skip the opening quote
        
        // Process everything until closing quote or end
        while (current && current->type != DQUOTE && current->type != QUOTE)
        {
            temp_value = get_token_value(current, envp, data, &split_env, &should_split);
            if (!temp_value)
            {
                free(concatenated_value);
                return NULL;
            }
            
            char *new_concat = ft_strjoin(concatenated_value, temp_value);
            free(concatenated_value);
            free(temp_value);
            concatenated_value = new_concat;
            
            current = current->next;
        }
        
        // Skip closing quote if present
        if (current && (current->type == DQUOTE || current->type == QUOTE))
            current = current->next;
        
        // Add the concatenated result
        if (concatenated_value && ft_strlen(concatenated_value) > 0)
        {
            data->s[data->l] = concatenated_value;
            data->l++;
        }
        else
        {
            free(concatenated_value);
        }
        
        return current;
    }
    
    // Handle standalone environment variables (state 3)
    if (head->state == 3)
    {
        char *expanded = check_env_general(head->content, envp);
        
        // Check if this should be split (standalone and contains spaces)
        if (should_split_env(head, head->next) && expanded && ft_strchr(expanded, ' '))
        {
            split_env = ft_split(expanded, ' ');
            if (split_env)
            {
                int i = 0;
                while(split_env[i])
                {
                    data->s[data->l] = ft_strdup(split_env[i]);
                    data->l++;
                    i++;
                }
                free_2d(split_env);
            }
            free(expanded);
        }
        else if (expanded && ft_strlen(expanded) > 0)
        {
            data->s[data->l] = expanded;
            data->l++;
        }
        else if (expanded)
        {
            free(expanded);
        }
        
        return head;
    }
    
    // Handle double quoted content (state 2)
    if (head->state == 2)
    {
        if (ft_double(head->content, envp, data) == 2)
            return NULL;
        if (data->s1 && ft_strlen(data->s1) > 0)
        {
            data->s[data->l] = ft_strdup(data->s1);
            data->l++;
        }
        return head;
    }
    
    // Handle single quoted content (state 1)
    if (head->state == 1)
    {
        if (head->content && ft_strlen(head->content) > 0)
        {
            data->s[data->l] = ft_strdup(head->content);
            data->l++;
        }
        return head;
    }
    
    // Handle regular words (state 0, type WORD)
    if (head->state == 0 && head->type == WORD)
    {
        if (head->content && ft_strlen(head->content) > 0)
        {
            data->s[data->l] = ft_strdup(head->content);
            data->l++;
        }
        return head;
    }

    return head;
}