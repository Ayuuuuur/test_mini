#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

enum e_type
{
   WORD = -1,
   WHITE_SPACE = ' ',
   NEW_LINE = '\n',
   NULL_TER = '\0',
   QUOTE = '\'',
   DQUOTE = '\"',
   ESCAPE = '\\',
   ENV = '$',
   PIPE_LINE = '|',
   REDIR_OUT = '>',
   REDIR_IN = '<',
   HERE_DOC = -2,
   DREDIR_OUT = -3,
   EXIT_STATUS
};

enum e_state
{
    GENERAL = 0,
    INQUOTE = 1,
    INDQUOTE = 2,
    ENV_STRING = 3
};


typedef struct s_parsing
{
    char *content;
    enum e_type type;
    enum e_state state;
    struct s_parsing *next;

}t_parsing;

typedef struct s_var
{
    char **s;
    int y;
    int z;
    char *s1;
    int in_file;
    int out_file;
    int k;
    int m;
    int i;
    int j;
    int l;
}t_var;

t_parsing *ft_save(char *av,t_parsing *head,enum e_type type,char c,enum e_state state, t_env *envp);
t_parsing *lexer(char *st, t_env *envs);
enum e_type check_token(char *str, int i);
void    error_print(char *str);
t_parsing *check_pipe(t_parsing *curr, int len);
t_parsing *check_quote(t_parsing *curr);
t_parsing *skip_space(t_parsing *head);
t_parsing *check_redirection(t_parsing *curr);
int is_allowed(char c);
int syntax_err(t_parsing *head);
int ft_redirect_out(t_parsing *head,t_var *data);
int ft_redirect_in(t_parsing *head , t_var *data);
int	ft_check_env(const char *s1, const char *s2, size_t n);
char *ft_charjoin(char *str,char c, t_env *envs);
int check_odd(char *str);
char *join_char(char *str, char c, t_env *envs);
t_parsing *check_space(t_parsing *head);
#endif