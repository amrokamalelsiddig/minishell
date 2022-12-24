/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:37:53 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 13:39:27 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_name(t_command *cmd)
{
	char	*str;

	if (!cmd->file)
	{
		str = ft_itoa(cmd->num);
		if (str)
		{
			cmd->file = ft_strjoin(g_info.minidir, str);
			g_info.files[cmd->num] = ft_strdup(cmd->file);
		}
		free(str);
		if (!g_info.files[cmd->num])
			return (MEM_ERR);
	}
	return (0);
}

static int	input(char *str, int fd, t_command *cmd)
{
	if (fd != STD_VAL)
		close(fd);
	if (!access(g_info.minidir, F_OK))
		unlink(g_info.minidir);
	if (str[1] != '<')
	{
		if (access(&str[1], F_OK))
			fd = NO_FILE;
		if (access (&str[1], R_OK) && !fd)
			fd = NO_READ;
		if (fd)
			g_info.error = fd;
		if (fd == STD_VAL)
			fd = open(&str[1], O_RDONLY);
		if (fd < 0)
			fd = OPN_ERR;
	}
	else
		fd = control(str, cmd);
	if (fd < 0)
		g_info.error = fd;
	else if (fd != HEREDOC && fd != SIG_END)
		fill_fd(&fd, 1);
	return (fd);
}

static int	output(char *str, int fd)
{
	int	check;

	check = 0;
	if (fd != STD_VAL)
		close(fd);
	if (!access(&str[1], F_OK) && access(&str[1], W_OK))
		check = NO_WRIT;
	if (check)
	{
		g_info.error = check;
		return (check);
	}
	if (str[1] != '>')
		check = open(&str[1], O_CREAT | O_WRONLY | O_TRUNC, 0622);
	else
		check = open(&str[2], O_CREAT | O_WRONLY | O_APPEND, 0622);
	if (check < 0)
	{
		check = OPN_ERR;
		g_info.error = check;
	}
	else
		fill_fd(&check, 1);
	return (check);
}

int	*redirect(char **red_arr, int fd_pair[2], t_command *cmd)
{
	int		counter;

	fd_pair[0] = STD_VAL;
	fd_pair[1] = STD_VAL;
	if (!red_arr)
		return (fd_pair);
	counter = 0;
	while (red_arr[counter])
	{
		if (red_arr[counter][0] == '<')
			fd_pair[0] = input(red_arr[counter], fd_pair[0], cmd);
		else if (red_arr[counter][0] == '>')
			fd_pair[1] = output(red_arr[counter], fd_pair[1]);
		if (fd_pair[0] < 0 || fd_pair[1] < 0)
			return (NULL);
		counter++;
		if (fd_pair[0] == SIG_END)
			return (NULL);
	}
	return (fd_pair);
}

int	command_len(t_command *command)
{
	t_command	*temp;
	int			count;

	temp = command;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}