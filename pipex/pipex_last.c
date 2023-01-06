/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:36:25 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/06 21:27:43 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
ERROR: This function takes a char pointer (str) 
and an integer (err) as arguments.
If str is not NULL, it writes "minishell: " and str to standard error. 
If err is 0, 
it writes ": " and the error message corresponding to errno, 
otherwise it writes ": command not found".
It then exits the program with a return value of err if err is not 0, 
otherwise it exits with a return value of 127.
*/

void	error(char *str, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!err)
	{
		ft_putendl_fd(strerror(errno), 2);
		err = 127;
	}
	else
		ft_putendl_fd("command not found", 2);
	exit(err);
}

/*
Get_Err: This function takes a char pointer (str) as an argument.
If the environment variable "PATH" is not set or str does not start 
with an alphabetical character, it returns 0. Otherwise, it returns 127.
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
child: This function takes a pointer to a t_command struct 
(commands) and an integer (fd_out) as arguments.
If fd_out is not STD_VAL, it redirects standard output to fd_out. Otherwise, 
it redirects standard output to the original standard output file descriptor.
It calls chk_builtin with commands as an argument and, if the return value 
is NONBLTN, 
it forks a new process. If the current process is the parent, it returns 
the pid of the child. 
If the current process is the child, it calls execve with commands->name, 
commands->argv, 
and g_info.env as arguments and stores the return value in g_info.last_prcs. 
If execve fails, 
it calls error with commands->name and If execve fails, it calls error 
with commands->name and the return value of get_err(commands->name) as arguments.
If the current process is the parent, it returns the pid of the child. 
Otherwise, it should not return as it has exited the process.
*/

static int	child(t_command *commands, int fd_out)
{
	int	pid;

	pid = 0;
	if (fd_out != STD_VAL)
		dup2(fd_out, STDOUT_FILENO);
	else
		dup2(g_info.std_fd[1], STDOUT_FILENO);
	if (chk_builtin(commands) == NONBLTN)
	{
		pid = fork();
		if (pid)
			return (pid);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name, get_err(commands->name));
	}
	return (pid);
}

/*
PIPELINE: This function takes a pointer to a t_command 
struct (commands) as an argument.
It calls check_fd_ret with commands->fd_redirs, NULL, and 
commands as arguments and returns -1 if check_fd_ret returns a non-zero value.
It calls child with commands and commands->fd_redirs[1] as 
arguments and stores the return value in a pid_t variable (pid).
If pid is less than 0, it returns -1. Otherwise, it sets 
commands->pid to pid and returns pid
*/

static int	pipeline(t_command *commands)
{
	pid_t	pid;
	int		*fd_redir;

	fd_redir = commands->fd_redirs;
	if (check_fd_ret(fd_redir, NULL, commands))
		return (-1);
	pid = child(commands, fd_redir[1]);
	if (pid < 0)
		return (-1);
	else if (pid > 0)
		commands->pid = pid;
	return (pid);
}

/*
Last Fork: This function takes a pointer to a 
t_command struct (commands) as an argument.
If commands->name is `NULL
*/

int	last_fork(t_command *commands)
{
	int		pid;

	if (commands->name)
		pid = pipeline(commands);
	else
		return (0);
	if (pid < 0)
		return (-1);
	if (pid == 1)
		return (1);
	return (0);
}
