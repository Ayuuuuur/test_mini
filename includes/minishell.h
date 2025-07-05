/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:05:11 by hind              #+#    #+#             */
/*   Updated: 2025/07/04 18:39:51 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_exit_status;

typedef struct s_lexer_data
{
	char			*str;
	int				i;
	int				len;
	enum e_state	state;
	enum e_type		quote_type;
	enum e_type		redirect_type;
	enum e_type		token_type;
	char			char_value;
	char			*content_str;
}					t_lexer_data;

typedef struct s_helpe
{
	t_env			*envs;
	enum e_state	state;
	enum e_type		c;
	char			*tmp;
	int				i;
	int				j;
	int				t;
	int				len;
}					t_help;

// struct for commands (list)
typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	struct s_cmd	*next;
}					t_cmd;

// struct pids
typedef struct process_id
{
	int				*pids;
	int				nbr_childs;
}					t_pids;

// builtins
int					ft_strcmp(char *s1, char *s2);
void				ft_exit(char **args, int is_child, t_env *envs);
int					ft_pwd(t_env *envs);
int					ft_env(char **args, t_env *envs);
int					ft_cd(char **args, t_env *envs);
int					ft_unset(char **args, t_env **envs);
int					ft_export(char **args, t_env **envs);
int					ft_echo(char **args);

int					check_flag_n(char *str);
int					ft_builtin(char **command, int is_child, t_env **envs);
int					ft_perror_cd(void);
int					print_error(char *str);

// list envs
void				add_env(t_env *newnode, t_env **head_list);
t_env				*list_envs(char **envp);
t_env				*new_env(char *env, char **envp);
char				*get_env_value(char *key, t_env *envs);
t_env				*build_new_envs(char **envs, char **envp, char flag);
char				*get_pwd(void);
char				**creat_mini_envp(void);

// free memory
void				free_list(t_env **head_env);
void				free_node(t_env *newnode);
void				free_arr_b(void **ptr);
void				free_list_cmd(t_cmd **cmd_list);
void				free_2d(char **str);

// find path
char				*executable_path(char *cmd, t_env *envs);
char				*get_path_env(t_env *envs);
char				*build_path(char *dirc, char *cmd, t_env *envs);

// envs
char				**envs_to_array(t_env *envs);
char				*join_key_value(t_env *temp);
int					len_list(t_env *temp);
char				*ft_strdup_env(const char *s1);
char				*ft_strjoin_env(char const *s1, char const *s2);
char				**ft_split_env(char const *s, char c);

// pipes
int					**piping(int lines, t_env *envs);
void				close_pipes(int nbr_pipes, int **ends);
void				waiting_childs(t_pids *pids);

// executore
void				ft_execve(t_env *envs, t_cmd *tmp_cmd);
int					duplication(int i, int len_cmd, int **pipes,
						t_cmd *tmp_cmd);
int					len_list_cmd(t_cmd *temp);
t_pids				*execute_commands(t_env **envs, t_cmd *tmp_cmd);

// error handling.
int					ft_perror(char *err_msg, int len_cmd, int **pipes);
void				message_error_exit(char *str, int is_child, t_env *envs);
void				display_exit(int is_child);

int					check_expand(t_parsing *head, t_env *envp, int len,
						t_cmd **cmd);
t_parsing			*expand(t_parsing *head, t_env *envp, t_var *data,
						t_cmd **cmd);
t_parsing			*heredoce(t_parsing *head, t_var *data, int flag,
						t_env *envp);
t_cmd				*ft_send(t_var *data, t_cmd *head, t_env *envs);
int					checker(t_parsing *head, t_env *envp, int len, t_cmd **cmd);
int					ft_double(char *str, t_env *envp, t_var *data);

// singals
void				my_handller(int sig);
void				set_signals_dfl(void);
void				sig_heredoc(int sig);
void				sig_ignore(void);
char				*expand_var(char *line, t_env *envp, int i);

// execution
int					*save_in_out(t_env *envs);
int					*saved_stdin_out(t_env *envs);
void				restore_stdin_out(int *saved_in_out);
int					space_skip_main(char *rdl);
int					skip_space_str(char *str);
char				*shell_prompt(t_env *envs);
int					lexer_checker(char *rdl, t_env *envs, t_cmd **cmd);
char				*read_line(t_env *envs, char *rdl);
int					send_to_execution(t_cmd *cmd, t_env *envs, int *arr_in_out,
						char *rdl);
int					main_loop(t_env *envs);
t_parsing			*handle_word_token(t_lexer_data *data, t_parsing *head,
						t_env *envs);
t_parsing			*handle_quote_token(t_lexer_data *data, t_parsing *head,
						t_env *envs);
t_parsing			*handle_word_space(t_lexer_data *data, t_parsing *head,
						t_env *envs);
t_parsing			*process_quote_content(t_lexer_data *data, t_parsing *head,
						t_env *envs);
t_parsing			*handle_quote_space(t_lexer_data *data, t_parsing *head,
						t_env *envs);

t_parsing			*ft_save(t_lexer_data *data, t_parsing *head, t_env *envs,
						char *content);
char				*check_env_general(char *str, t_env *envp);
int					ft_split_expand(char **s1, t_var *data, t_env *envp);
int					is_standalone_env_var(t_parsing *head);
int					handle_env_split(t_parsing *head, t_env *envp, t_var *data);
char				*get_token_value(t_parsing *head, t_env *envp, t_var *data);
t_parsing			*check_redin_expand(t_parsing *head, t_var *data);
t_parsing			*check_pipe_expand(t_parsing *head, t_var *data,
						t_cmd **cmd, t_env *envp);
t_parsing			*check_herdoc_expand(t_parsing *head, t_var *data,
						t_env *envp);
t_parsing			*check_redout_expand(t_parsing *head, t_var *data);
t_parsing			*check_env_expand(t_parsing *head, t_var *data,
						t_env *envp);
int					handle_env_split(t_parsing *head, t_env *envp, t_var *data);
char				*get_token_value(t_parsing *head, t_env *envp, t_var *data);
t_parsing			*handle_heredoc(t_parsing *head, t_var *data, t_env *envp);
t_parsing			*handle_redirect_out(t_parsing *head, t_var *data);
t_parsing			*check_redir_herdoc(t_parsing *head, t_var *data,
						t_env *envp);
t_parsing			*help_concat(char **concatenated_value, t_parsing *current,
						t_env *envp, t_var *data);
int					check_state_exp(t_parsing *current);
int					if_helper(t_parsing **current);
int					helper_loop_two(t_parsing *current);
int					helper_loop_exp(t_parsing *current);
t_parsing			*check_redin_expand(t_parsing *head, t_var *data);
t_parsing			*check_pipe_expand(t_parsing *head, t_var *data,
						t_cmd **cmd, t_env *envp);
t_parsing			*check_herdoc_expand(t_parsing *head, t_var *data,
						t_env *envp);
t_parsing			*check_redout_expand(t_parsing *head, t_var *data);
t_parsing			*check_env_expand(t_parsing *head, t_var *data,
						t_env *envp);
int					add_split_tokens(char **split_env, t_var *data,
						t_env *envp);
int					is_standalone_env_var(t_parsing *head);
int					ft_split_expand(char **s1, t_var *data, t_env *envp);
char				*check_env_general(char *str, t_env *envp);
char				*handle_dollar_sign(char *str, int *i, t_env *envp,
						char *s);
char				*ft_charjoin(char *str, char c, t_env *envp);
int					check_help_env(int *i, char *str);
char				*process_env_variable(char *str, int *i, t_env *envp);
char				*handle_special_dollar(char *str, int *i, t_env *envp,
						char *s);
char				*handle_env_variable(char *str, int *i, t_env *envp,
						char *s);
char				*join_char(char *str, char c, t_env *envs);
int					check_parth(char *str);
int					handle_special_cases(char *str, t_var *data, t_env *envp);
int					handle_parentheses(char *str, t_var *data, t_env *envp);
int					handle_single_parentheses(char *str, t_var *data,
						t_env *envp);
int					handle_env_variable_1(char *str, t_var *data, t_env *envp);
int					handle_invalid_var(t_var *data, t_env *envp);
int					handle_valid_var(t_var *data, char *var_value, t_env *envp);
char				*find_env_value(char *var_name, t_env *envp);
int					extract_var_name(char *str, t_var *data, char **var_name);
char				*init_result_string(t_env *envp);
int					extract_var_name_length(char *line, int *i);
char				*find_env_var_value(char *line, int start, int len,
						t_env *envp);
char				*process_dollar_variable(char *line, int *i, char *result,
						t_env *envp);
char				*expand_var(char *line, t_env *envp, int i);
char				*build_delimiter(t_parsing *head, int *flag, t_env *envp);
void				setup_heredoc_signals(int *fds);
char				*process_heredoc_line(char *line, int flag, t_env *envp);
void				write_line_to_pipe(int fd, char *line);
void				heredoc_input_loop(int *fds, char *delimiter, int flag,
						t_env *envp);
void				run_heredoc(int *fds, t_parsing *head, int flag,
						t_env *envp);
void				closing(int *fds);
void				error_msg_heredoc(char *delimiter);
int					wait_heredoc(t_var *data, int pid, int *fds);
t_parsing			*skip_delimiter(t_parsing *head);
t_parsing			*heredoce(t_parsing *head, t_var *data, int flag,
						t_env *envp);
t_parsing			*skip_whitespace(t_parsing *current);
t_parsing			*get_next_content_token(t_parsing *current);
int					should_merge_tokens(t_parsing *current);
void				merge_export_tokens(t_parsing *current, t_env *envs);
t_parsing			*save_quote_content(t_lexer_data *data, t_parsing *head,
						char *tmp, t_env *envs);
char				*build_word_content(t_lexer_data *data, t_env *envs);
#endif