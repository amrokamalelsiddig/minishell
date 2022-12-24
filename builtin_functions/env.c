/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:36:45 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/24 10:36:46 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
