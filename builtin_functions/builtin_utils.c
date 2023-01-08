/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:35:42 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:43:53 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
ERR MSG:
function that prints an error message to the standard error output. 
It takes two arguments:
str: a string representing the name of a file or directory
option: an integer that indicates the type of error. 
If option is 0, then the error message indicates that the 
file or directory specified by str does not exist. If option is 
non-zero, then the error message indicates that the $HOME environment 
variable is not set.
*/

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

/*
GET STR:
takes in an array of strings envp and a string reference, 
and returns a string starting from the character after the 
first occurrence of reference in any of the strings in envp. 
If reference is not found in any of the strings in envp, the 
function returns NULL
*/

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

/*
FREEDOM:
takes in a double pointer to an array of 
strings arr and frees the memory associated 
with the array and its elements.
*/

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

/*
OUTPUT PROMPTS:
outputs the environment variables in the format declare -x NAME="VALUE"
to the standard output, one per line. It reads the environment variables 
from the global env array and outputs them in this format until it reaches 
the end of the array or an error occurs. If an error occurs, the function 
terminates and the error flag in the global g_info variable is set to 1.
*/

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
