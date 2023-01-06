/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:37:53 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 01:15:32 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
SET_NAME: This function sets the file field of the t_command 
struct pointed to by cmd to a file name based on the 
value of the num field of the struct. The file name is 
constructed by concatenating the global variable 
g_info.minidir with the string representation of cmd->num. 
If the file field is already set or an error occurs, 
the function returns MEM_ERR. Otherwise, the function returns 0.
*/

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

/*
input: This function handles input redirection for a command. If 
the value of fd is not equal to STD_VAL, the function closes fd. 
If the file specified by g_info.minidir exists, the function unlinks it. 
If the second character in str is not '<', the function checks if the 
file specified by str exists and has read permission. If the file does 
not exist or does not have read permission, the function sets g_info.error 
to the appropriate error code and returns it. If the file exists and has 
read permission, the function opens the file for reading and stores the 
file descriptor in fd. If fd is less than 0, the function sets fd to OPN_ERR 
and g_info.error to fd. If fd is not HEREDOC or SIG_END, the 
function stores fd in the global variable g_info.filed. The function 
returns fd. If the second character in str is '<', the function calls the 
control() function and returns its result.
*/

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

/*
output: This function handles output redirection for a command. 
If the value of fd is not equal to STD_VAL, the function closes fd. 
If the file specified by str exists and does not have write permission, 
the function sets g_info.error to NO_WRIT and returns it. If the second 
character in str is not '>', the function opens the file specified by 
str for writing and overwriting and stores the file descriptor in fd. 
If the second character in str is '>', the function opens the file 
specified by str for writing and appending and stores the file descriptor 
in fd. If fd is less than 0, the function sets fd to OPN_ERR and g_info.error 
to fd. The function stores fd in the global variable g_info.filed if fd is not 
an error code. The function returns fd.
*/

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

/*
redirect: This function handles input and output redirection for a 
command by calling input() and output() as appropriate. 
The input and output redirection commands are specified by 
the elements of the array pointed to by red_arr. The function 
stores the file descriptors for input and output in the fd_pair 
array, which it returns. If an error occurs, the function returns NULL.
*/

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

/*
command_len: This function returns the number of elements in the 
linked list of t_command structs pointed to by command
*/

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
