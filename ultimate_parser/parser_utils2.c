/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:24:37 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:38:16 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
PRINT MSG:
This function takes a pointer to an integer stat 
and processes it to print an appropriate message 
based on the value of stat. The message indicates 
the status of a process that has terminated or stopped.
*/

void	print_msg(int *stat)
{
	int	status;

	status = *stat;
	if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		g_info.last_prcs = SIG_BCK;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_info.last_prcs = SIG_END;
		g_info.sig = 0;
	}
	else if (!WIFSIGNALED(status))
		g_info.last_prcs = WEXITSTATUS(status);
}

/*
GET EXIT:
This function takes a pointer to a t_command struct,
and waits for all the processes in the linked list to 
terminate. The function returns 0 after all processes have 
terminated.
*/

int	get_exit(t_command *commands)
{
	int	status;

	status = 0;
	while (commands)
	{
		if (commands->pid > 0)
		{
			waitpid(commands->pid, &status, 0);
			if (status == 127)
				g_info.last_prcs = 127;
			else if (WIFEXITED(status))
				g_info.last_prcs = WEXITSTATUS(status);
			else
				print_msg(&status);
		}
		commands = commands->next;
	}
	return (0);
}

/*
EMPTY FD ARR:
This function closes all open file descriptors 
and removes all temporary files created for redirection.
*/

static void	empty_fd_arr(void)
{
	int	temp;

	temp = 0;
	while (g_info.filed[temp])
	{
		if (temp == 32)
			break ;
		close(g_info.filed[temp]);
		temp++;
	}
	ft_bzero(g_info.filed, 32 * sizeof (int));
	temp = 0;
	while (temp < 16)
	{
		if (!access(g_info.files[temp], F_OK))
			unlink(g_info.files[temp]);
		free(g_info.files[temp]);
		temp++;
	}
	ft_bzero(g_info.files, 16 * sizeof (char *));
}

/*
GET FD:
This function takes a pointer to a t_command struct,
and processes the redirection instructions in the 
linked list. The function returns 1 if an error occurred, 
and 0 otherwise.
*/

static int	get_fd(t_command *command)
{
	int			ret;
	t_command	*temp;

	ret = 0;
	temp = command;
	while (temp)
	{
		temp->num = ret;
		ret++;
		temp = temp->next;
	}
	ret = 0;
	while (!ret && command)
	{
		redirect(command->rdrct, command->fd_redirs, command);
		if (command->fd_redirs[0] == SIG_END)
		{
			ret = 1;
			continue ;
		}
		command = command->next;
	}
	return (ret);
}

/*
COMMAND CENTER:
This function takes a string input and a pointer to a 
pointer to a pointer to a string envp, and processes 
the string as a command. The function parses the string, 
sets up the necessary pipes and file redirections, and 
executes the command. The function returns 0 after the 
command has been executed.
*/

int	command_center(char *input, char ***envp)
{
	int			ret;

	g_info.commands = parse_string(input);
	if (g_info.commands)
	{
		if (!get_fd(g_info.commands))
		{
			ret = pipex(g_info.commands);
			if (ret == 1)
				g_info.last_prcs = 1;
			else if (ret)
				g_info.last_prcs = 127;
		}
		dup2(g_info.std_fd[0], STDIN_FILENO);
		dup2(g_info.std_fd[1], STDOUT_FILENO);
	}
	get_exit(g_info.commands);
	free_command(g_info.commands);
	empty_fd_arr();
	*envp = g_info.env;
	errno = 0;
	g_info.error = 0;
	return (0);
}
