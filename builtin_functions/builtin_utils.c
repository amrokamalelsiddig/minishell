/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:35:42 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/24 10:35:51 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_msg(char *str, int option)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (!option)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
		ft_putendl_fd("$HOME not set", 2);
}

char	*get_str(char **envp, char *reference)
{
	char	*str;

	str = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, reference, ft_strlen(reference)))
		{
			str = *envp;
			break ;
		}
		envp += 1;
	}
	if (str)
		str += ft_strlen(reference);
	return (str);
}

void	*freedom(char ***arr)
{
	char	**temp;
	int		index;

	temp = *arr;
	index = 0;
	while (temp[index])
	{
		free(temp[index]);
		index++;
	}
	free(temp);
	return (NULL);
}

void	output_prompts(void)
{
	int		index;
	char	*name;
	char	*value;

	index = 0;
	while (g_info.env[index] && !g_info.error)
	{
		name = ft_strcut(g_info.env[index], "=");
		if (!name)
		{
			raise_error(MEMORY_ERROR, NULL);
			return ;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		value = ft_strchr(g_info.env[index], '=') + 1;
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		index++;
		free(name);
	}
}
