/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:36:58 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/06 21:27:41 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
ERR_UTILS: This function has no arguments. 
It checks the value of g_info.error and calls 
ft_putendl_fd with an appropriate error message 
and 2 (stderr) as the file descriptor.
*/

static void	err_utils(void)
{
	if (g_info.error == (uint8_t)NO_FILE)
		ft_putendl_fd("No such file or directory", 2);
	if (g_info.error == (uint8_t)NO_READ)
		ft_putendl_fd("Permission denied", 2);
	if (g_info.error == (uint8_t)NO_WRIT)
		ft_putendl_fd("Permission denied", 2);
	if (g_info.error == (uint8_t)MEM_ERR)
		ft_putendl_fd("Memory error", 2);
	if (g_info.error == (uint8_t)OPN_ERR)
		ft_putendl_fd("Permission denied", 2);
}

/*
ERROR_PIPEX: This function takes a string (str) as an argument.
It prints "minishell: " to stderr.
If str is not NULL, it prints str and ": " to stderr.
If g_info.error is 0, it prints the error message 
associated with errno to stderr. Otherwise, it calls err_utils.
*/

void	error_pipex(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!g_info.error)
		ft_putendl_fd(strerror(errno), 2);
	else
		err_utils();
}

/*
chk builtin: This function takes a pointer to a 
t_command struct (commands) as an argument.
It initializes a variable code to NONBLTN.
It compares commands->name to each of the built-in 
commands in g_info.bltn and calls the corresponding built-in function with 
commands->argv as an argument. It stores the return value in code.
If code is not NONBLTN, it sets g_info.last_prcs to code.
It returns code.
*/

int	chk_builtin(t_command *commands)
{
	char	*name;
	int		code;

	code = NONBLTN;
	name = commands->name;
	if (!ft_strncmp(name, g_info.bltn[0], 5))
		code = ft_echo1(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[1], 3))
		code = ft_cd1(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[2], 4))
		code = ft_pwd1();
	else if (!ft_strncmp(name, g_info.bltn[3], 4))
		code = ft_export(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[4], 4))
		code = ft_unset(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[5], 4))
		code = ft_env1(commands->argv);
	else if (!ft_strncmp(name, g_info.bltn[6], 5))
		code = ft_exit(commands->argv);
	if (code != NONBLTN)
		g_info.last_prcs = code;
	return (code);
}

/*
DUPS: 
sets up the standard input and output file descriptors for
 a command by duplicating them to the given file descriptor 
 values in fd_redir. It takes in two arguments:

fd_redir: an array of two integers representing the 
file descriptor values to be used as the standard input and output file 
descriptors.
cmd: a pointer to a t_command structure representing 
the command being executed.
The function first checks if the first element in 
fd_redir is set to a value other than STD_VAL or HEREDOC. 
If it is, then it duplicates the file descriptor value to the standard 
input file descriptor using dup2. If the value is HEREDOC, then it opens 
the file specified in cmd->file for reading, duplicates it to the standard input 
file descriptor, and then closes the file.

Next, the function checks if the second element in fd_redir is set to a 
value other than STD_VAL. If it is, then it duplicates the file descriptor 
value to the standard output file descriptor using dup2.

Finally, the function closes the file descriptors specified in fd_redir 
if they are not set to STD_VAL.
*/

static void	dups(int fd_redir[2], t_command *cmd)
{
	int	fd;

	if (fd_redir[0] != STD_VAL && fd_redir[0] != HEREDOC)
		dup2(fd_redir[0], STDIN_FILENO);
	else if (fd_redir[0] == HEREDOC)
	{
		fd = open(cmd->file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (fd_redir[0] != STD_VAL && fd_redir[0] != HEREDOC)
		close(fd_redir[0]);
	if (fd_redir[1] != STD_VAL)
	{
		dup2(fd_redir[1], STDOUT_FILENO);
		close(fd_redir[1]);
	}
}

/*
check fd ret: This function takes in two arrays of 
integers fd_redir and fd, 
and a pointer to a t_command structure cmd. 
The function first checks if either of the values in fd_redir are negative. 
If either of them is, 
it means that there was an error while opening a file for redirection and 
the function closes the 
file descriptors in fd (if fd is not NULL) and returns an error code.
Next, the function checks if either of the values in fd_redir is equal to the 
constant HEREDOC, which indicates that the command is a here document. 
If either value is HEREDOC, the function calls the 
here_doc function with the delimiter string 
from cmd and the cmd structure itself as arguments. 
The here_doc function creates a temporary file, 
opens it for writing, and writes the user input 
(terminated by the delimiter string) to the file. T
he here_doc function returns the process ID of the 
child process it creates. 
If the here_doc function returns a negative value, 
the check_fd_ret function returns an error code.
Finally, the function calls the dups function with 
fd_redir and cmd as arguments. 
The dups function duplicates the file descriptors in 
fd_redir onto the standard input 
and output file descriptors (STDIN_FILENO and STDOUT_FILENO) 
and closes the file descriptors 
in fd_redir if they are not equal to the constant STD_VAL 
(which indicates that no redirection is needed).
The check_fd_ret function returns 0 if it successfully 
opens and redirects the necessary 
file descriptors, and an error code otherwise.
*/

int	check_fd_ret(int fd_redir[2], int fd[2], t_command *cmd)
{
	if (fd_redir[0] < 0 || fd_redir[1] < 0)
	{
		if (fd)
		{
			close(fd[INPUT_END]);
			close(fd[OUTPUT_END]);
		}
		if (fd_redir[0] < 0 && fd_redir[1] != STD_VAL)
			close(fd_redir[1]);
		if (fd_redir[1] < 0 && fd_redir[0] != STD_VAL)
			close(fd_redir[0]);
		error_pipex(NULL);
		return (-1);
	}
	if (fd_redir[0] != STD_VAL || fd_redir[1] != STD_VAL)
		dups(fd_redir, cmd);
	return (0);
}
