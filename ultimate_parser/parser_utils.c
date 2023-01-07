/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:49:45 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 14:20:52 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_split_path(void)
{
	char	**path;
	char	*env;

	env = ft_getenv(g_info.env, "PATH");
	if (env)
	{
		path = ft_split(env, ':');
		if (!path)
			return (raise_error(MEMORY_ERROR, NULL));
	}
	else
		path = NULL;
	return (path);
}

char	*insert_content(char *str, int start, int end, char *content)
{
	char	*first_part;
	char	*second_part;
	char	*temp;
	char	*new;

	first_part = ft_strndup(str, start);
	second_part = ft_strdup(&str[end]);
	temp = ft_strjoin(first_part, content);
	new = ft_strjoin(temp, second_part);
	if (!new)
		raise_error(MEMORY_ERROR, NULL);
	ft_free_strs(temp, first_part, second_part);
	return (new);
}

void	*raise_error(char *message, char *str)
{
	char	*specify;

	g_info.error = 1;
	if (!str)
		ft_putendl_fd(message, 2);
	else
	{
		ft_putstr_fd(message, 2);
		if (str[0] == str[1])
			specify = ft_strndup(str, 2);
		else
			specify = ft_strndup(str, 1);
		if (!specify)
			return (raise_error(MEMORY_ERROR, NULL));
		ft_putstr_fd("`", 2);
		ft_putstr_fd(specify, 2);
		ft_putendl_fd("'", 2);
		free(specify);
	}
	return (NULL);
}

int	is_builtin_command(char *name)
{
	if (!ft_strncmp("echo", name, ft_strlen(name)))
		return (1);
	if (!ft_strncmp("cd", name, ft_strlen(name)))
		return (1);
	if (!ft_strncmp("pwd", name, ft_strlen(name)))
		return (1);
	if (!ft_strncmp("export", name, ft_strlen(name)))
		return (1);
	if (!ft_strncmp("unset", name, ft_strlen(name)))
		return (1);
	if (!ft_strncmp("env", name, ft_strlen(name)))
		return (1);
	if (!ft_strncmp("exit", name, ft_strlen(name)))
		return (1);
	return (0);
}

char	*add_full_path(char *str, char **path)
{
	char	*absolute_path;
	int		index;
	char	*temp;

	if (!str || *str == '/' || !path || !access(str, F_OK)
		|| is_builtin_command(str))
		return (str);
	temp = ft_strjoin("/", str);
	index = 0;
	while (path[index])
	{
		absolute_path = ft_strjoin(path[index], temp);
		if (!access(absolute_path, F_OK))
		{
			free(str);
			free(temp);
			return (absolute_path);
		}
		free(absolute_path);
		index++;
	}
	free(temp);
	return (str);
}
