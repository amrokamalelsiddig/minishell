/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:36:13 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/05 17:20:35 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	change_pwd(char **envp)
{
	char	*pwd;
	int		index;

	index = 0;
	pwd = getcwd(NULL, 0);
	while (envp[index] && ft_strncmp(envp[index], "PWD=", ft_strlen("PWD=")))
		index++;
	if (envp[index])
		free(envp[index]);
	envp[index] = ft_strjoin("PWD=", pwd);
	free(pwd);
}

static void	change_oldpwd(char **envp)
{
	char	*oldpwd;
	int		index;

	index = 0;
	oldpwd = getcwd(NULL, 0);
	while (envp[index] && ft_strncmp(envp[index], "OLDPWD=",
			ft_strlen("OLDPWD=")))
		index++;
	if (envp[index])
		free(envp[index]);
	envp[index] = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
}

static int	change_dir(char *path, char **envp)
{
	int		check;

	change_oldpwd(envp);
	if (!path)
	{
		check = 1;
		err_msg(NULL, 1);
	}
	else
		check = chdir(path);
	change_pwd(envp);
	if (check)
		check = 1;
	else if (check == -1)
		return (check);
	return (check);
}

int home_flags(char *argv)
{
	if ((ft_strncmp(argv,";",1) == 0) || \
	(ft_strncmp(argv,"-",1) == 0) || \
	(ft_strncmp(argv,"~",1) == 0))
		return (0);
	return (1);
}

int	ft_cd1(char **argv)
{
	char	*home;
	int		result;

	home = get_str(g_info.env, "HOME=");
	if (!argv[1])
		result = change_dir(home, g_info.env);
	else
		result = change_dir(argv[1], g_info.env);
	if (result && argv[1])
		err_msg(argv[1], 0);
	return (result);
}
