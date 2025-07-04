/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:02:05 by marvin            #+#    #+#             */
/*   Updated: 2025/07/03 22:26:09 by nahilal          ###   ########.fr       */
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
    result = ft_strdup("", envp);
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
                        result = ft_strjoin(result, tmp->value, envp);
                        if(!result)
                            return(NULL);
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            else
                result = ft_charjoin(result,'$',envp);
        }
        else
        {
            result = join_char(result, line[i], envp);
            if (!result)
                return (NULL);
            i++;
        }
    }
    return (result);
}
void closing(int *fds)
{
    close(fds[0]);  // Clean up file descriptors
    close(fds[1]);
}

void error_msg_heredoc(char *delimiter)
{
    ft_putstr_fd("minishell: warning: here-document at line delimited by end-of-file (wanted `", 2);
    ft_putstr_fd(delimiter, 2);
    ft_putstr_fd("`)\n", 2);
}

void run_heredoc(int *fds, t_parsing *head, int flag, t_env *envp)
{
    char *line;
    char *expanded_line;
    char *delimiter;

    delimiter = ft_strdup(head->content,envp);
    head = head->next;
    while(head)
    {
        if(head->type == PIPE_LINE || head->type == SPACE)
            break;
        if(head->type == DQUOTE || head->type == QUOTE)
            flag = 1;
        else
            delimiter = ft_strjoin(delimiter,head->content,envp);
        head = head->next;
    }
    signal(SIGINT, sig_heredoc);
    close(fds[0]);
    while (1)
    {
        line = readline("> ");
        if(ft_strcmp(line, delimiter) == 0)
            break;
        if(flag == 0)
        {
            expanded_line = expand_var(line, envp, 0);
            free(line);
            line = expanded_line;
        }
        if(!line)
        {
            error_msg_heredoc(delimiter);
            break;
        }
        write(fds[1], line, ft_strlen(line));
        write(fds[1], "\n", 1);
        free(line);
    }
    close(fds[1]);
    exit(0);
}

int wait_heredoc(t_var *data, int pid, int *fds)
{
    int state;

    sig_ignore();
    waitpid(pid, &state, 0);
    close(fds[1]);
    if (WIFEXITED(state))
    {
        g_exit_status = WEXITSTATUS(state);
        if(g_exit_status == 130)
        {
            close(fds[0]);  // Clean up file descriptors
            return(2);
        }
    }
    data->in_file = fds[0];
    return(0);
}
t_parsing *skip_delimiter(t_parsing *head)
{
    if(!head->next)
        return(head);
    head = head->next;
    while(head)
    {
        if(!head->next || (head->next && head->next->type == PIPE_LINE) || head->type == PIPE_LINE || head->type == SPACE)
            break;
        head = head->next;
    }
    return(head);
}
t_parsing *heredoce(t_parsing *head,t_var *data, int flag, t_env *envp)
{
    int *fds;
    int pid;

    fds = g_collector(2 * sizeof(int), envp);
    if(pipe(fds) == -1)
        return(NULL);
    pid = fork();
    if(pid == -1)
        return(closing(fds), NULL);
    if (pid == 0)
        run_heredoc(fds, head,flag,envp);    
    else
    {
        if(wait_heredoc(data, pid, fds) == 2)
            return(NULL);
    }
    head = skip_delimiter(head);
    return(head);
}

