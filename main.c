/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:47:30 by nahilal           #+#    #+#             */
/*   Updated: 2025/06/12 18:03:28 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <readline/history.h>

int G_EXIT_STATUS = 0;

int skip_space_str(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != ' ')
            return(1);
        i++;
    }
    return(0);
}


int *saved_stdin_out(void)
{
    int *in_out;

    in_out = (int *)malloc(sizeof(int) * 2);

    in_out[0] = dup(STDIN_FILENO);
    in_out[1] = dup(STDOUT_FILENO);
    if(in_out[0] == -1 || in_out[1] == -1)
        perror("minishell");
    return(in_out);
}

void restore_stdin_out(int *saved_stdin_out)
{
    if(dup2(saved_stdin_out[0], STDIN_FILENO) == -1)
        perror("dup2 ");
    if(dup2(saved_stdin_out[1], STDOUT_FILENO) == -1)
        perror("dup2 ");
    close(saved_stdin_out[0]);
    close(saved_stdin_out[1]);
}

char *shell_prompt(t_env *envs)
{
	char *cwd;
	char *prompt;

	cwd = getcwd(NULL, 0);
	if(!cwd)
		cwd = get_env_value("PWD", envs);
	prompt = ft_strjoin(cwd, " $> ");
	return(prompt);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char    *rdl;
    int     *arr_in_out;

    t_cmd   *cmd = NULL;
	t_cmd   *commads_in_out;
	t_env   *envs;
    t_pids  *pids; // struct of process ids 
    t_parsing   *head;

    // (void)envp;
	envs = list_envs(envp); //save
	while (1)
	{
        arr_in_out = saved_stdin_out();  //save
        if(arr_in_out[0] == -1 || arr_in_out[1] == -1)
        {
            free(arr_in_out);
            free_list(&envs);
            return 0;
        }

        // prompt
		rdl = readline(shell_prompt(envs));
		if (!rdl)  // Handle Ctrl+D (EOF)
		{
			printf("exit\n"); // notify message
			break;
		}

		// parssing 
        head = lexer(rdl);
        t_parsing *h = head;
        while(h)
        {
            printf("content => %s\n",h->content);
            printf("state => %d\n",h->state);
            printf("type => %d\n",h->type);
            printf("********************\n");
            h = h->next;
        }
        
		if(skip_space_str(rdl) == 1)
            add_history(rdl);
        if(checker(head,envs,ft_strlen(rdl),&cmd) == 2)
            continue;
        commads_in_out = cmd;
                
        
        int i = 0;
        while(commads_in_out)
        {
            i = 0;
            while(commads_in_out->full_cmd[i])
                printf("full cmd ==> |%s|\n",commads_in_out->full_cmd[i++]);
            printf("in_file ==> %d\n",commads_in_out->in_file);
            printf("out_file ==> %d\n",commads_in_out->out_file);
            printf("********************\n");
            commads_in_out = commads_in_out->next;
        }

        //execution
        commads_in_out = cmd;
        if(commads_in_out)
        {
            pids = execute_commands(&envs, commads_in_out);
            if(!pids)
                return(0);       
            restore_stdin_out(arr_in_out);
            waiting_childs(pids);
        }
        cmd = NULL;
	}
	return (0);
}

// handle exit status  ~
//     --> export should return with failure when not a valid name , but at same time should continue execution when i have many args.
//     (export 2A=1 B=1 --> error msg + exit fail 1 + B exported)
//     /////////////////////////////////////////
//     >> export 2A=22 B=22
//     bash: export: `2A=22': not a valid identifier
//     >> echo $?
//     1
//     >> export | grep B
//     declare -x B="22"
//     ///////////////////////////////////////// solution (edit GLOBAL status)

//     --> env with args (correct or not) should return error ?
//     (cases when env used with command ) fix it eith childs also

//     --> check exit status of childs proccess is return it correctly 

///////////////////////////////////////////////////////////////////////////
//////////////////////////////testing////////////////////////////////////// 
// $> ABC=hola
// echo $ (if $ only you should send it )
// echo $?
// echo $?$ 
// echo $:$= | cat -e
// echo my shit terminal is [$TERM4]
// echo $9HOME >>>>>>>> HOME
// echo $TERM$HOME
// echo $hola*
// testttt -----------> 134
// 
// a=ls -la >> $a
// export a="ls -la"
// export $DONTEXIST >>>>> behave like export only.
// export "" >>>> bash: export: `': not a valid identifier
// export HOLA=$HOME >>>> shouldn't give a error
// export HOLA=bon(jour >>>>>>> should give -> bash: syntax error near unexpected token `('
// 
// cd $PWD >>>>> should go to home.
// cd $HOME >>>>> and home not set should give error >>>>>>> minishell: cd: HOME not set.
// error handling when rm -rf a, when we are already in a/b/c
// handle if remove pwd , and getcwd failed.
// thats correct ->>> cd srcs >>>> minishell: No such file or directory
// pwd -p >>>>> if should handle that >>>>>>>>>> bash: pwd: -p: invalid option
// cd "". 
// 
// 
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// exit (argument + overflow) ~

// handle signals ~

// garbeg collectore ~


// handell redirections ~solved~

// handel heredoc ~solved~

// split functions ~done~

// handle waitpid ~solved~
// -> store the pids ~ done ~
// void	wait_procces(int pid)
// {
//     int	st;
//     int	i;

//     i = 0;
//     waitpid(pid, &st, 0);
//     if (WEXITSTATUS(st))
//         MY_EXIT_STATUS = WEXITSTATUS(st);
//     if (WIFSIGNALED(st))
//     {
//         MY_EXIT_STATUS = st + 128;
//         if (MY_EXIT_STATUS == 131)
//             printf("Quit: 3\n");
//     }
//     while (wait(&st) > i)
//         i = 0;
// }

// error handling, in all functions  ~ 
// --> handle close behave -> remove close from duplication ~done~ .
// --> check envs in builtins . ~done~
// -----> env should not work with envs==NULL ~solved~
// -----> perror or strerror instead of printf ~solved~


// */
