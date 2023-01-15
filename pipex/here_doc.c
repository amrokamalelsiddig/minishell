/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:35:17 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/15 19:10:48 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Cancel CMD DOC: This function is a signal 
handler for the SIGINT signal.
When the signal is received, it writes a newline 
character to standard output and then exits the program with a 
return value of SIG_END
*/
static void	cancel_cmd_doc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(SIG_END);
}

/*
SET_SINGAL: This function sets the signal handlers 
for the SIGQUIT, SIGTERM, and SIGINT signals.
It sets the handler for SIGQUIT to SIG_IGN 
(ignore the signal).
It sets the handler for SIGTERM to SIG_IGN 
(ignore the signal).
It sets the handler for SIGINT to cancel_cmd_doc 
(the function defined earlier).
*/

static void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, cancel_cmd_doc);
}

/*
get_readstr: This function takes a char pointer (str) 
and an integer (fd) as arguments.
It writes str to fd, frees str, and sets the signal 
handler for SIGINT to set_signal.
It then reads a new line from the user using readline 
and stores the result in str.
*/

static void	get_readstr(char **str, int fd)
{
	ft_putendl_fd(*str, fd);
	free(*str);
	set_signal();
	*str = readline("> ");
}

/*
Here_Doc: This function takes a char pointer (delimiter) and 
a pointer to a t_command struct (cmd) as arguments.
It forks a new process and, if the current process is the parent, 
it returns the pid of the child. If the current process is the child, 
it continues executing.
It opens a file specified by cmd->file and sets the file descriptor to fd.
It sets the signal handler for SIGINT to set_signal.
It reads a line from the user using readline and 
stores the result in a char pointer (str).
It enters a loop that continues until str is NULL or 
the first ft_strlen(delimiter) characters of str match delimiter. 
In each iteration of the loop, it calls get_readstr to write str to fd, 
read a new line from the user, and store the result in str.
After the loop, if str is not NULL, it frees str and closes fd.
It then exits the child process with a return value of 0.
*/

static int	here_doc(char *delimiter, t_command *cmd)
{
	char	*str;
	int		fd;
	pid_t	pid;

	dup2(g_info.std_fd[0], STDIN_FILENO);
	dup2(g_info.std_fd[1], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid > 0)
		return (pid);
	fd = open(cmd->file, O_CREAT | O_WRONLY | O_TRUNC, 0622);
	delimiter += 2;
	set_signal();
	str = readline("> ");
	while (str && ft_strncmp(str, delimiter, ft_strlen(delimiter)))
		get_readstr(&str, fd);
	if (str)
		free(str);
	close(fd);
	exit(0);
}

/*
Control: This function takes a char pointer (delim) and a pointer to
 a t_command struct (cmd) as arguments.
It calls a function set_name with cmd as an argument. If set_name returns a 
non-zero value, control returns MEM_ERR.
It calls here_doc with delim and cmd as arguments and stores the return value 
in a pid_t variable (pid).
It waits for the child process with the pid pid to finish and stores the exit 
status in an int variable (status).
If the exit status of the child process is SIG_END, it sets the global 
variable g_info.last_prcs to SIG_END, g_info.sig to 0, and returns SIG_END.
Otherwise, it returns HEREDOC.
*/

int	control(char *delim, t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (set_name(cmd))
		return (MEM_ERR);
	pid = here_doc(delim, cmd);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == SIG_END)
	{
		g_info.last_prcs = SIG_END;
		g_info.sig = 0;
		return (SIG_END);
	}
	return (HEREDOC);
}
