/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:37:25 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/24 10:37:27 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_unset(char *name, char *argv)
{
	char	*variable;
	int		len;

	variable = ft_strjoin(argv, "=");
	if (!variable)
	{
		raise_error(MEMORY_ERROR, NULL);
		return (-1);
	}
	len = (int)ft_strlen(variable);
	if (!ft_strncmp(name, variable, len))
	{
		free(variable);
		return (1);
	}
	free(variable);
	return (0);
}

char	**do_unset(char *argv)
{
	char	**new;
	int		envp_index;
	int		new_index;

	new = malloc(sizeof(char *) * (ft_arrlen(g_info.env)));
	if (!new)
		return (raise_error(MEMORY_ERROR, NULL));
	envp_index = 0;
	new_index = 0;
	while (g_info.env[envp_index] && !g_info.error)
	{
		if (!is_unset(g_info.env[envp_index], argv))
		{
			new[new_index] = ft_strdup(g_info.env[envp_index]);
			if (!new[new_index])
				raise_error(MEMORY_ERROR, NULL);
			new_index++;
		}
		envp_index++;
	}
	new[new_index] = NULL;
	return (new);
}

void	unset_error(char *argv, int *code)
{
	ft_putstr_fd("bash: unset: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	*code = 1;
}

int	is_correct(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isalnum(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **argv)
{
	char	**new;
	int		code;
	int		index;

	code = 0;
	index = 1;
	while (argv[index] && !g_info.error)
	{
		if (!is_correct(argv[index]))
			unset_error(argv[index], &code);
		else if (ft_getenv(g_info.env, argv[index]))
		{
			new = do_unset(argv[index]);
			free_arr(&g_info.env);
			g_info.env = new;
		}
		index++;
	}
	if (code)
		g_info.error = 1;
	return (g_info.error);
}
