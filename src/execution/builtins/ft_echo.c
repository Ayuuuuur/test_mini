#include "../../../includes/minishell.h"

int check_flag_n(char *str)
{
	int i;
	
	i = 1; // to skip the '-' cuz already check it
 	while (str[i])
	{
		if(str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int ft_echo(char **args)
{
	int i;
	int check;

	i = 1;
	check = 0;

	while (args[i])
	{
		if(args[i][0] == '-' && check_flag_n(args[i]) == 1) // check the first char is - ?
			check = 1;
		else
			break;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if(args[i + 1]) //no space after the last arg
			printf(" ");
		i++;
	}
	if(check == 0)
		printf("\n");

	return(EXIT_SUCCESS);
}

