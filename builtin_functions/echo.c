/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:36:30 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:52:57 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
is a function that writes a string to the stdout. 
It takes in a string str and an integer flag as arguments. 
If flag is 1, it writes a space character after the string. 
If flag is 2, it writes a newline character after the string.
*/

static void	ft_putstr(char *str, int flag)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	if (flag == 1)
		write(STDOUT_FILENO, " ", 1);
	if (flag == 2)
		write(STDOUT_FILENO, "\n", 1);
}

/*
FT CYCLE:
is a function that iterates through an array of strings 
and writes each string to the stdout with a space character 
after it, except for the last string which is written with a 
newline character after it. It takes in an integer flag 
(which is not used in the function), an integer index which 
is the starting index of the array and a string array argv as arguments.
*/

static void	ft_cycle(int flag, int index, char **argv)
{
	while (argv[index])
	{
		if (!argv[index + 1])
			ft_putstr(argv[index], flag);
		else
			ft_putstr(argv[index], 1);
		index++;
	}
}

/*
FT ECHO:
 is a function that reads in a string array argv 
 and writes the strings to the stdout with a space 
 character after each string except for the last string 
 which is written with a newline character after it. 
 If the first string in argv is "-n", the function does not 
 write the newline character after the last string. If argv 
 has less than 2 strings, the function writes a newline character
*/

int	ft_echo1(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc < 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (argc == 2 && !ft_strncmp(argv[1], "-n", 3))
		return (0);
	if (argc > 2 && !ft_strncmp(argv[1], "-n", 3))
		ft_cycle(0, 2, argv);
	else
		ft_cycle(2, 1, argv);
	return (0);
}
