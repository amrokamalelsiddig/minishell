/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:36:45 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:54:10 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
get env:
takes in an environment envp and a string name, 
and returns the value of the environment variable 
with the given name. If there is no such environment 
variable, it returns NULL.
*/

char	*ft_getenv(char **envp, char *name)
{
	char	*variable;
	int		len;
	int		index;

	variable = ft_strjoin(name, "=");
	if (!variable)
		return (NULL);
	len = (int)ft_strlen(variable);
	index = 0;
	while (envp && envp[index])
	{
		if (!ft_strncmp(envp[index], variable, len))
		{
			free(variable);
			return (envp[index] + len);
		}
		index++;
	}
	free(variable);
	return (NULL);
}

/*
FT ENV:
takes in an array of strings argv and does the following:
If argv has more than one element, it prints an error message 
to STDERR_FILENO and returns 1.
If the environment variable PATH is not defined, it prints an 
error message to STDERR_FILENO and returns 127.
Otherwise, it prints all the environment variables in g_info.
env to STDOUT_FILENO and returns 0
*/

int	ft_env1(char **argv)
{
	int	i;

	if (argv && argv[1])
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
		return (1);
	}
	if (!ft_getenv(g_info.env, "PATH"))
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (127);
	}
	i = 0;
	while (g_info.env && g_info.env[i])
	{
		ft_putendl_fd(g_info.env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
