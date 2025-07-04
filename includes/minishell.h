
#ifndef MINISHELL_H
#define MINISHELL_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include "libft.h"
#include "parsing.h"

extern int g_exit_status;


typedef struct s_lexer_data
{
    char *str;
    int i;
    int len;
    enum e_state state;
    enum e_type quote_type;
    enum e_type redirect_type;
}t_lexer_data;

//norm struct

typedef struct s_helpe
{
	t_env *envs;
	enum e_state state;
    enum e_type c;
    char *tmp;
	int i;
    int j;
    int t;
    int len;
}t_help;
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
	int *pids;
	int nbr_childs;
} t_pids;


int	ft_strcmp(char *s1, char *s2);

// builtins 
int ft_pwd(t_env *envs);
int ft_env(char **args, t_env *envs);
void ft_exit(char **args, int is_child, t_env *envs);
int ft_cd(char **args, t_env *envs);
int ft_unset(char **args, t_env **envs);
int ft_export(char **args, t_env **envs);
int ft_echo(char **args);

int check_flag_n(char *str);
int ft_builtin(char **command,int is_child, t_env **envs);
int ft_perror_cd();
int	print_error(char *str);


// list envs
void    add_env(t_env *newnode, t_env **head_list);
t_env   *list_envs(char **envp);
t_env   *new_env(char *env, char **envp); //0 if a normal env //1 if exported (just the name) 
char    *get_env_value(char *key, t_env *envs);
t_env 	*build_new_envs(char **envs, char **envp);
char	*get_pwd();
char **creat_mini_envp();

// free memory
void	free_list(t_env **head_env);
void    free_node(t_env *newnode);
void	free_arr_b(void **ptr);
void	free_list_cmd(t_cmd **cmd_list);
void	free_2d(char **str);

// find path
char	*executable_path(char *cmd, t_env *envs);
char	*get_path_env(t_env *envs);
char	*build_path(char *dirc, char *cmd, t_env *envs);

// envs 
char    **envs_to_array(t_env *envs);
char    *join_key_value(t_env *temp);
int     len_list(t_env *temp);
char	*ft_strdup_env(const char *s1);
char	*ft_strjoin_env(char const *s1, char const *s2);
char	**ft_split_env(char const *s, char c);

//pipes
int		**piping(int lines, t_env *envs);
void	close_pipes(int nbr_pipes, int **ends);
void	waiting_childs(t_pids *pids);

// executore
void	ft_execve(t_env *envs, t_cmd *tmp_cmd);
int	duplication(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd);
int		len_list_cmd(t_cmd *temp);
t_pids	*execute_commands(t_env **envs, t_cmd *tmp_cmd);

// error handling. 
int	ft_perror(char *err_msg, int len_cmd, int **pipes);

// parssing testtt
int 		checker(t_parsing *head,t_env *envp, int len,t_cmd **cmd);
t_parsing	*expand(t_parsing *head,t_env *envp,t_var *data,t_cmd **cmd);
int			ft_double(char *str, t_env *envp, t_var *data);
int			check_expand(t_parsing *head,t_env *envp,int len,t_cmd **cmd);
t_cmd		*ft_send(t_var *data, t_cmd *head, t_env *envs);
t_parsing *heredoce(t_parsing *head,t_var *data, int flag, t_env *envp);


//singals
void	my_handller(int sig);
void	set_signals_dfl();
void    sig_heredoc(int sig);
void	sig_ignore();
char *expand_var(char *line, t_env *envp, int i);



//execution
int	*save_in_out(t_env *envs);
int	*saved_stdin_out(t_env *envs);
void	restore_stdin_out(int *saved_in_out);
int	space_skip_main(char *rdl);
int	skip_space_str(char *str);
char	*shell_prompt(t_env *envs);
int	lexer_checker(char *rdl, t_env *envs, t_cmd **cmd);
char	*read_line(t_env *envs, char *rdl);
int	send_to_execution(t_cmd *cmd, t_env *envs, int *arr_in_out, char *rdl);
int	main_loop(t_env *envs);
t_parsing	*handle_word_token(t_lexer_data *data, t_parsing *head, t_env *envs);
t_parsing	*handle_quote_token(t_lexer_data *data, t_parsing *head, t_env *envs);
t_parsing	*handle_word_space(t_lexer_data *data, t_parsing *head, t_env *envs);
t_parsing	*process_quote_content(t_lexer_data *data, t_parsing *head, t_env *envs);
t_parsing	*handle_quote_space(t_lexer_data *data, t_parsing *head, t_env *envs);






char	*check_env_general(char *str, t_env *envp);
char	*process_dollar_env(char *str, int *i, char *s, t_env *envp);
char	*find_env_match(char *str, int *i, char *s, t_env *tmp);
void	skip_env_chars(char *str, int *i);
int		ft_split_expand(char **s1, t_var *data, t_env *envp);
int		is_standalone_env_var(t_parsing *head);
int		handle_env_split(t_parsing *head, t_env *envp, t_var *data);
int		process_split_array(char **split_env, t_var *data, t_env *envp);
char	*get_token_value(t_parsing *head, t_env *envp, t_var *data);
t_parsing	*check_redin_expand(t_parsing *head, t_var *data);
t_parsing	*check_pipe_expand(t_parsing *head, t_var *data, t_cmd **cmd, t_env *envp);
t_parsing	*check_herdoc_expand(t_parsing *head, t_var *data, t_env *envp);
t_parsing	*check_redout_expand(t_parsing *head, t_var *data);
t_parsing	*check_env_expand(t_parsing *head, t_var *data, t_env *envp);
t_parsing	*expand_help_process(t_parsing *current, t_env *envp, t_var *data, char **temp_value);
int		check_quote_continuation(t_parsing *current);
int		check_quote_break(t_parsing *current);
t_parsing	*handle_quote_end(t_parsing *current, t_var *data, char *concatenated_value, t_cmd **cmd, t_env *envp);
t_parsing	*check_quote_expand(t_parsing *head, t_var *data, t_cmd **cmd, t_env *envp);
t_parsing	*process_quote_loop(t_parsing *current, char **concatenated_value, t_env *envp, t_var *data);
#endif