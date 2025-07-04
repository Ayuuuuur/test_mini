#include "../../../includes/minishell.h"

void set_signals_dfl()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void sig_ignore()
{
    signal(SIGINT, SIG_IGN); // ignore sigint while parent wait child to dont affect parent 
    signal(SIGQUIT, SIG_IGN);
}

void my_handller(int sig)
{
    (void)sig;
    ft_putchar_fd('\n', 1);
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
    g_exit_status = 130;
}


void    sig_heredoc(int sig)
{
    (void) sig;
    ft_putchar_fd('\n', 1);
    // clean_memory(&(envs->head_gc));
    exit(130); /////////////////////// check that in heredoc 
}

