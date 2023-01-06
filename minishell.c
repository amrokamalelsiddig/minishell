/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:03 by kpanikka          #+#    #+#             */
/*   Updated: 2023/01/07 01:14:44 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	g_info;

/*
FILL BLTN: This function allocates an array of 8 char pointers and 
initializes them to point to strings containing the names of built-in commands.
It returns the initialized array.
*/

static char	**fill_bltn(void)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(8, sizeof (char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup("echo");
	ret[1] = ft_strdup("cd");
	ret[2] = ft_strdup("pwd");
	ret[3] = ft_strdup("export");
	ret[4] = ft_strdup("unset");
	ret[5] = ft_strdup("env");
	ret[6] = ft_strdup("exit");
	while (i < 7)
	{
		if (!ret[i])
			return (free_arr(&ret));
		i++;
	}
	return (ret);
}

/*
FILL MINIDIR: This function takes an array of char pointers 
(argv) as an argument.It gets the current working directory,
changes the current working directory to the directory specified 
by argv[0], gets the current working directory again, and stores 
it in the global variable g_info.minidir.
It then appends "/." to g_info.minidir and changes the current 
working directory back to the original directory.
*/

static int	fill_minidir(char **argv)
{
	char	*temp;
	char	*temp1;

	temp = getcwd(NULL, 0);
	temp1 = ft_strrchr(argv[0], '/');
	ft_bzero(temp1, ft_strlen(temp1));
	chdir(argv[0]);
	g_info.minidir = getcwd(NULL, 0);
	chdir(temp);
	temp1 = g_info.minidir;
	g_info.minidir = ft_strjoin(temp1, "/.");
	free(temp);
	free(temp1);
	return (0);
}

/*
INIT_INFO: This function takes argc, argv, and envp as arguments, 
but does not use argc.
It calls fill_minidir to initialize g_info.minidir.
It sets g_info.std_fd[0] and g_info.std_fd[1] to duplicates of the 
file descriptors for standard input and standard output, respectively.
It calls fill_bltn to initialize g_info.bltn.
It sets g_info.env to a copy of envp.
It sets g_info.error to 0.
It allocates and initializes g_info.filed and g_info.files to empty arrays.
*/

static void	init_info(int argc, char **argv, char **envp)
{
	int		temp_i;
	char	*temp_s;
	char	*temp_s1;

	(void)argc;
	fill_minidir(argv);
	g_info.std_fd[0] = dup(STDIN_FILENO);
	g_info.std_fd[1] = dup(STDOUT_FILENO);
	g_info.bltn = fill_bltn();
	g_info.env = ft_arrdup(envp, 10);
	if (!g_info.env)
		return ;
	temp_s = get_str(g_info.env, "SHLVL=");
	if (temp_s)
	{
		temp_i = ft_atoi(temp_s) + 1;
		temp_s1 = ft_itoa(temp_i);
		if (temp_i > 1 && temp_s1)
			ft_memcpy(temp_s, temp_s1, ft_strlen(temp_s1));
		free(temp_s1);
	}
	g_info.error = 0;
	g_info.filed = ft_calloc(32, sizeof (int));
	g_info.files = ft_calloc(16, sizeof (char *));
}
/*
PROMPT: This function reads lines of input from the user using 
the readline function and passes them to the command_center function.
It also appears to handle some signals and maintain a history 
of previously entered commands.
It returns 0 when it is finished.
*/

int	prompt(char **envp)
{
	char	*str[1000];
	int		index;

	index = 0;
	set_signals();
	str[index] = readline("\033[1;35mminishell$ \033[0m");
	while (str[index])
	{
		command_center(str[index], &envp);
		if (ft_strlen(str[index]) > 0 && g_info.sig != 1)
			add_history(str[index]);
		free(str[index]);
		index++;
		if (index == 1000)
			index = 0;
		set_signals();
		str[index] = readline("\033[1;35mminishell$ \033[0m");
	}
	if (str[index])
		free(str[index]);
	return (0);
}

/*
MAIN: This function calls init_info to initialize some global variables.
It then calls prompt to enter the main loop of the shell.
When prompt returns, main frees some memory and returns 0.
*/

int	main(int ac, char **av, char **env)
{
	init_info(ac, av, env);
	if (!g_info.env || !g_info.bltn || !g_info.filed || !g_info.files)
		error(NULL, 0);
	env = g_info.env;
	set_signals();
	prompt(env);
	return (g_info.error);
}
