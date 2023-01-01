/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:36:25 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/24 20:54:47 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_err(char *str)
{
	if (!ft_getenv(g_info.env, "PATH"))
		return (0);
	if (!ft_isalpha(*str))
		return (0);
	return (127);
}

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
		{
			return (pid);
			// exit(0);
		}
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		//error(commands->name, get_err(commands->name));
		get_err(commands->name);
		if (!(g_info.last_prcs  != -1 ))
			ft_putstr_fd(COMMAND_ERROR,1);
	}
	return (pid);
}

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