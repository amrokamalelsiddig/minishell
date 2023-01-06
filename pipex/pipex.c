/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:38:18 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 00:33:25 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
FILL_FD: This function modifies the global variable g_info.
filed by storing the file descriptors in fd_arr starting 
at the first empty index in g_info.filed. 
The number of file descriptors stored is specified by count. 
If there are no empty indices left in g_info.filed or count is 0, 
the function exits without storing any file descriptors.
*/

void	fill_fd(int *fd_arr, int count)
{
	int	temp;

	temp = 0;
	while (g_info.filed[temp] && temp < 32)
		temp++;
	while (count-- > 0)
	{
		if (temp == 32)
			break ;
		g_info.filed[temp] = *fd_arr;
		temp++;
		fd_arr++;
	}
}

/*
GET_ERR: This function returns an error code based on the value 
of the input string str. 
If the environment variable PATH is not set, the function returns 0. 
If str does not start with an alphabetical character, the function returns 0. 
Otherwise, the function returns 127.
*/

static int	get_err(char *str)
{
	if (!ft_getenv(g_info.env, "PATH"))
		return (0);
	if (!ft_isalpha(*str))
		return (0);
	return (127);
}

/*
CHILD: This function creates a child process using fork(), 
which is a copy of the calling process. The child process 
executes a command specified by commands, which is a pointer 
to a t_command struct containing the name and arguments of 
the command to be executed. The standard output of the command 
is redirected to the write end of the pipe specified by fd if 
fd_out is equal to STD_VAL. If the command is a built-in shell 
command, it is executed directly in the child process. Otherwise, 
the child process calls execve() to execute the command. 
If an error occurs, the function calls error() and passes it 
the name of the command and an error code returned by get_err(). 
The function returns the child process ID if the child process is 
successfully created, or 0 if the child process is the one being created.
*/

static int	child(int fd[2], t_command *commands, int fd_out)
{
	int	pid;

	pid = 0;
	if (fd_out == STD_VAL)
		dup2(fd[INPUT_END], STDOUT_FILENO);
	if (chk_builtin(commands) == NONBLTN)
	{
		pid = fork();
		if (pid)
			return (pid);
		signal_in_child();
		close(fd[OUTPUT_END]);
		if (fd_out == STD_VAL)
			dup2(fd[INPUT_END], STDOUT_FILENO);
		close(fd[INPUT_END]);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name, get_err(commands->name));
	}
	return (pid);
}

/*
PIPELINE: This function creates a pipeline between two processes 
by calling child() 
to create the child process and executing a command in it. 
The standard input of the child process is redirected from the read 
end of the pipe specified by fd, and the standard output of the child 
process is redirected to the write end of the pipe if the file descriptor 
for standard output in the t_command struct pointed to by commands is equal 
to STD_VAL. If the function returns a value greater than or equal to 0, 
it closes the read and write ends of the pipe specified by fd. 
The function returns 
the child process ID if the child process is successfully created, 1 
if the command is a built-in shell command that should be executed in the 
parent process, SIG_END if the command is NULL, or -1 if an error occurs.
*/

static int	pipeline(t_command *commands, int fd[2])
{
	pid_t	pid;
	int		*fd_redir;

	if (!commands->name)
		return (0);
	fd_redir = commands->fd_redirs;
	if (check_fd_ret(fd_redir, fd, commands))
		return (-1);
	pid = child(fd, commands, fd_redir[1]);
	if (pid < 0)
		return (-1);
	if (pid >= 0)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
	}
	return (pid);
}

/*
PIPEX: This function creates a pipeline of processes to 
execute a list of commands specified by commands, which 
is a pointer to a linked list of t_command structs. 
The function creates a pipe for each pair of consecutive 
commands in the list, and calls pipeline() to create a 
child process and execute the first command in the pair. 
If the command is a built-in shell command that should be 
executed in the parent process, the function returns 1. 
If the command is NULL, the function returns 0. If an error occurs, 
the function returns -1. After all of the commands have 
been executed, the function calls last_fork() to create a child process for
*/

int	pipex(t_command *commands)
{
	int			fd[2];
	int			status;
	int			pid;

	signal_in_pipes();
	while (command_len(commands) - 1)
	{
		if (pipe(fd))
			return (-1);
		pid = pipeline(commands, fd);
		if (pid == 1)
			return (1);
		else if (pid == SIG_END)
			return (0);
		else if (pid > 0)
			commands->pid = pid;
		else if (pid < 0)
			return (-1);
		if (pid && WIFEXITED(status))
			g_info.last_prcs = WEXITSTATUS(status);
		commands = commands->next;
	}
	if (last_fork(commands) == 1)
		return (1);
	return (0);
}
