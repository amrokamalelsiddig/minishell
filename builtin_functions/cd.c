/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:36:13 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:50:33 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
CHANGE PWD:
This function updates the environment 
variable "PWD" to the current working 
directory in the environment envp.
*/

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

/*
OLD PWD:
This function updates the environment variable 
"OLDPWD" to the current working directory in the 
environment envp.
*/

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

/*
CHANGE DIR:
This function changes the current working directory to the 
directory specified by path. If path is NULL, the function 
attempts to change to the home directory specified by the environment 
variable "HOME". If the directory change is successful, the function 
updates the environment variables "PWD" and "OLDPWD" in envp to reflect 
the change. The function returns 0 if the directory change was successful, 
and -1 if it was not.
*/

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

/*
HOME FLAGS:
This function checks the string argv 
to see if it is either ";", "-", or "~", 
and returns 0 if it is any of those values and 1 otherwise.
*/

int	home_flags(char *argv)
{
	if ((ft_strncmp(argv, ";", 1) == 0)
		|| (ft_strncmp(argv, "-", 1) == 0)
		|| (ft_strncmp(argv, "~", 1) == 0))
		return (0);
	return (1);
}

/*
FT CD1:
This function implements the cd shell builtin. 
If argv has a second element (i.e., argv[1] exists), 
the function attempts to change to the directory specified
by argv[1]. If argv[1] does not exist, the function attempts 
to change to the home directory specified by the environment variable 
"HOME". If the directory change is successful, the function returns 0.
If the directory change is not successful and argv[1] exists, the function 
prints an error message and returns -1. If argv[1] does not exist, 
the function returns 1.
*/

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
