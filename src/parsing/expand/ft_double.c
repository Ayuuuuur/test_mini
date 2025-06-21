/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:35:55 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 19:30:20 by claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *join_char(char *str, char c)
{
    char *result;
    size_t len;
    
    if (!str)
    {
        result = malloc(2);
        if (!result)
            return (NULL);
        result[0] = c;
        result[1] = '\0';
        return (result);
    }
    
    len = ft_strlen(str);
    result = malloc(len + 2);
    if (!result)
    {
        free(str);
        return (NULL);
    }
    ft_strlcpy(result, str, len + 1);
    result[len] = c;
    result[len + 1] = '\0';
    
    free(str);
    return (result);
}
int check_parth(char *str)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(str[i])
    {
        if(str[i] == '(')
            len++;
        i++;
    }
    i = 0;
    while(str[i] && len >= 0)
    {
        if(str[i] == ')')
            len--;
        i++;
    }
    if(len != 0)
        return(0);
    return (2);
}
int ft_double(char *str, t_env *envp, t_var *data)
{
    t_env *tmp;
    int len;
    int start;

    data->s1 = malloc(2);
    if (!data->s1)
        return (2);
    data->s1[0] = '\0';
    data->i = 0;
    while (str[data->i])
    {
        if (str[data->i] != '$')
        {
            data->s1 = join_char(data->s1, str[data->i]);
            if (!data->s1)
                return (2);
        }
        else if (str[data->i] == '$')
        {
            data->j = data->i + 1;
            if (str[data->j] == '\0')
            {
                data->s1 = join_char(data->s1, '$');
                if (!data->s1)
                    return (2);
                break;
            }
            if (str[data->j] == '(' && str[data->j + 1] == '(')
            {
                if(check_parth(str + data->i) == 0)
                    return (error_print("syntax error \"unclosed parentheses\"\n"), 2);
                data->j += 2;
                while (str[data->j] != ')' || str[data->j + 1] != ')')
                {
                    if (str[data->j] == '\0')
                        return (error_print("syntax error \"unclosed parentheses\"\n"), 2);
                    data->j++;
                }
                data->s1 = ft_strjoin(data->s1, "0");
                if (!data->s1)
                    return (2);
                data->i = data->j + 2;
                continue;
            }
            else if (str[data->j] == '(')
            {
                if(check_parth(str + data->i) == 0)
                    return (error_print("syntax error \"unclosed parentheses\"\n"), 2);
                data->j++;
                start = data->j;

                while (str[data->j] != ')')
                {
                    if (str[data->j] == '\0')
                        return (error_print("syntax error \"unclosed parentheses\"\n"), 2);
                    data->j++;
                }
                data->s1 = ft_strjoin(data->s1, ft_substr(str, start, data->j - start));
                if (!data->s1)
                    return (2);
                
                data->i = data->j + 1;
                continue;
            }
            else
            {
                start = data->j;
                while (str[data->j] && (ft_isalnum(str[data->j]) || str[data->j] == '_'))
                    data->j++;
                len = data->j - start;
                if (len > 0)
                {
                    tmp = envp;
                    while (tmp)
                    {
                        if (ft_strcmp(tmp->key, ft_substr(str, start, len)) == 0)
                        {
                            data->s1 = ft_strjoin(data->s1, tmp->value);
                            if (!data->s1)
                                return (2);
                            break;
                        }
                        tmp = tmp->next;
                    }
                    data->i = data->j - 1;
                }
                else
                {
                    data->s1 = join_char(data->s1, '$');
                    if (!data->s1)
                        return (2);
                }
            }
        }
        data->i++;
    }
    return (0);
}