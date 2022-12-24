/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:35:17 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 13:35:56 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cancel_cmd_doc(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	exit(SIG_END);
}

static void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, cancel_cmd_doc);
}

static void	get_readstr(char **str, int fd)
{
	ft_putendl_fd(*str, fd);
	free(*str);
	set_signal();
	*str = readline("> ");
}

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