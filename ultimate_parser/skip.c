/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:53:12 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:40:58 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
SKIP ARGUMENT:
This function takes a string str and returns the 
number of characters in the first argument in the 
string. An argument is a sequence of characters in 
str that is not separated by whitespace or any of 
the characters <>|. If an argument is inside quotes 
(single or double), the quotes and their contents are 
considered part of the argument.
*/

int	skip_argument(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(" <>|\t\v\0", str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quotes(&str[i]);
		i++;
	}
	return (i);
}

/*
SKIP QUOTES:
This function takes a string str and returns the 
number of characters in the contents of the quotes 
at the start of the string. If the quotes are not 
properly closed, the function sets the global error flag.
*/

int	skip_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		raise_error(NEWL_ERROR, NULL);
	return (i);
}

/*
SKIP REDIRECT:
This function takes a string str and returns the 
number of characters in the argument of the redirect 
operator (>, <, or >>) at the start of the string. 
If the argument is not properly formatted or is missing, 
the function sets the global error flag.
*/

int	skip_redirect(char *str)
{
	char	arrow;
	int		i;

	i = 0;
	arrow = str[i++];
	if (str[i] == arrow)
		i++;
	while (str[i] && ft_strchr(" \t\v", str[i]))
		i++;
	if (!str[i])
		raise_error(NEWL_ERROR, NULL);
	else if (ft_strchr("|<>", str[i]))
		raise_error(TOKEN_ERROR, &str[i]);
	else
	{
		while (str[i] && !ft_strchr(" <>|\t\v", str[i]))
		{
			if (str[i] == '\'' || str[i] == '"')
				i += skip_quotes(&str[i]);
			i++;
		}
	}
	return (i);
}
