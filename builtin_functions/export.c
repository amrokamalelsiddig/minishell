/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:37:11 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/10 20:02:07 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*export_error(char **new)
{
	free_arr(&new);
	raise_error(MEMORY_ERROR, NULL);
	return (NULL);
}

char	**change_env(char *new_str, char **envp, char *name)
{
	int		index;
	char	**new;

	index = 0;
	new = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	while (envp[index])
	{
		if (!ft_strncmp(name, envp[index], ft_strlen(name)))
			new[index] = ft_strdup(new_str);
		else
			new[index] = ft_strdup(envp[index]);
		if (!new[index])
			return (export_error(new));
		index++;
	}
	new[index] = NULL;
	return (new);
}

char	**add_env(char *new_str, char **envp)
{
	int		index;
	char	**new;

	new = malloc(sizeof(char *) * (ft_arrlen(envp) + 2));
	if (!new)
		return (raise_error(MEMORY_ERROR, NULL));
	index = 0;
	while (envp[index] && !g_info.error)
	{
		new[index] = ft_strdup(envp[index]);
		if (!new[index])
			return (export_error(new));
		index++;
	}
	new[index] = ft_strdup(new_str);
	if (!new[index])
		return (export_error(new));
	new[++index] = NULL;
	return (new);
}

char	**do_export(char *argv)
{
	char	**new;
	char	*name;

	name = ft_strcut(argv, "=");
	if (!name)
		return (raise_error(MEMORY_ERROR, NULL));
	if (!ft_getenv(g_info.env, name))
		new = add_env(argv, g_info.env);
	else
		new = change_env(argv, g_info.env, name);
	free(name);
	return (new);
}

int	ft_export(char **argv)
{
	char	**new;
	int		index;
	int		flag;

	flag = 0;
	index = 1;
	if (!argv[index])
		output_prompts();
	while (argv[index] && !g_info.error)
	{
		if (ft_strchr(argv[index], '='))
		{
			flag = 1;
			new = do_export(argv[index]);
			free_arr(&g_info.env);
			g_info.env = new;
		}
		index++;
	}
	if (!(flag))
		g_info.error = 1;
	if (g_info.error)
		return (1);
	return (g_info.error);
}
