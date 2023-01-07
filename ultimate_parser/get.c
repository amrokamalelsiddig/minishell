/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:49:22 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 14:02:59 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
GET QUOTES CONTENT:
This function takes in a string str and 
returns a copy of the substring between the 
first and second occurrences of the character 
*str. If the second occurrence of *str is not 
found, the function returns NULL.
*/

char	*get_quotes_content(char *str)
{
	char	*content;
	char	quote;
	int		i;

	i = 0;
	quote = *str++;
	while (str[i] && str[i] != quote)
		i++;
	content = ft_strndup(str, i);
	if (!content)
		raise_error(MEMORY_ERROR, NULL);
	return (content);
}

/*
GET DOLLAR:
This function takes in a string str 
and returns a copy of the substring 
between the first dollar sign and the 
next space, tab, vertical tab, or null 
terminator. If str begins with $?, the 
function returns a copy of "?".
*/

char	*get_dollar(char *str)
{
	char	*dollar;
	int		i;

	i = 1;
	if (str[i] == '?')
		dollar = ft_strdup("?");
	else
	{
		while (!ft_strchr(" <>$'\"\t\v\0", str[i]))
			i++;
		dollar = ft_strndup(&str[1], i - 1);
	}
	if (!dollar)
		raise_error(MEMORY_ERROR, NULL);
	return (dollar);
}

/*
GET DOLLAR FOR EXPAND:
This function is similar to get_dollar, 
but it returns the substring between the 
first dollar sign and the next space, tab, 
vertical tab, colon, :, <, >, $, single quote, 
double quote, or null terminator. If str begins 
with $?, the function returns a copy of "?".
*/

char	*get_dollar_for_expand(char *str)
{
	char	*dollar;
	int		i;

	i = 1;
	if (str[i] == '?')
		dollar = ft_strdup("?");
	else
	{
		while (!ft_strchr(" :<>$'\"\t\v\0", str[i]))
			i++;
		dollar = ft_strndup(&str[1], i - 1);
	}
	if (!dollar)
		raise_error(MEMORY_ERROR, NULL);
	return (dollar);
}

/*
GET REDIRECT:
This function takes in a string str and 
returns a copy of the substring following 
the first redirect found in str. If no 
redirect is found, the function returns NULL.
*/

char	*get_redirect(char *str)
{
	char	*redirect;
	char	*temp;
	int		i;

	i = skip_redirect(str);
	temp = ft_strndup(str, i);
	if (!temp)
		return (raise_error(MEMORY_ERROR, NULL));
	redirect = ft_skipnchar(temp, i, " \t\v");
	if (!redirect)
		raise_error(MEMORY_ERROR, NULL);
	free(temp);
	return (redirect);
}

/*
GET ARGUMENT:
This function takes in a string str and 
returns a copy of the substring up to the 
first space, tab, vertical tab, or null 
terminator found in str. If no such character 
is found, the function returns a copy of str.
*/

char	*get_argument(char *str)
{
	char	*argument;
	int		i;

	i = skip_argument(str);
	argument = ft_strndup(str, i);
	if (!argument)
		raise_error(MEMORY_ERROR, NULL);
	return (argument);
}
