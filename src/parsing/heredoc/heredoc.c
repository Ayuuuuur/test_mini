/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:02:05 by marvin            #+#    #+#             */
/*   Updated: 2025/05/23 17:02:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *expand_var(char *line, t_env *envp, int i)
{
    char *result;
    int start;
    int len;
    t_env *tmp;
    
    if (!line)
        return (NULL);
    result = ft_strdup("");
    if (!result)
        return (NULL);
    while (line[i])
    {
        if (line[i] == '$')
        {
            i++;
            start = i;
            while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                i++;
            len = i - start;   
            if (len > 0)
            {
                tmp = envp;
                while (tmp)
                {
                    if (ft_strcmp(tmp->key, ft_substr(line, start, len)) == 0)
                    {
                        result = ft_strjoin(result, tmp->value);
                        if(!result)
                            return(NULL);
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        }
        else
        {
            result = join_char(result, line[i]);
            if (!result)
                return (NULL);
            i++;
        }
    }
    return (result);
}

int heredoce(char *limiter, t_var *data, int flag, t_env *envp)
{
    char *line;
    char *processed_line;
    int fds[2];
    
    if (!limiter || !data || pipe(fds) == -1)
        return (2);
    
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, limiter) == 0)
        {
            if (line)
                free(line);
            break;
        }
        if (flag == 0)
        {
            processed_line = expand_var(line, envp,0);
            if (!processed_line)
            {
                free(line);
                close(fds[1]);
                close(fds[0]);
                return (2);
            }
        }
        else
        {
            processed_line = ft_strdup(line);
            if (!processed_line)
            {
                free(line);
                close(fds[1]);
                close(fds[0]);
                return (2);
            }
        }
        
        write(fds[1], processed_line, ft_strlen(processed_line));
        write(fds[1], "\n", 1);
        
        free(line);
        free(processed_line);
        
    }
    
    close(fds[1]);
    data->in_file = fds[0];
    return (0);
}