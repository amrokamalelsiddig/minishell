/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:03 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/23 13:26:00 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	g_info;

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

int	main(int ac, char **av, char **env)
{
	init_info(ac, av, env);
	if (!g_info.env || !g_info.bltn || !g_info.filed || !g_info.files)
		printf("asojihaisuhdsh\n");
	env = g_info.env;
	set_signals();
	prompt(env);
	return (0);
}
