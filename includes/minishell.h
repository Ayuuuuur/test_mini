
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

extern int G_EXIT_STATUS;

//execution

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
char	**creat_mini_envp();

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
void	duplication(int i, int len_cmd, int **pipes, t_cmd  *tmp_cmd);
int		len_list_cmd(t_cmd *temp);
t_pids	*execute_commands(t_env **envs, t_cmd *tmp_cmd);

// error handling. 
void	ft_perror(char *err_msg, int len_cmd, int **pipes);

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
#endif