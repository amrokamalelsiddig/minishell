/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:49:09 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 13:56:16 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
DISCLOSE QUOTES:
This function takes in a string pointer str and an integer 
pointer i, 
and expands the quoted substring starting at index *i in 
*str. It does 
this by calling get_quotes_content with the address of 
the character at 
index *i in *str, and then using the returned string to 
call insert_content 
with *str, *i, *i + 2 + the length of the content string, 
and the content string. 
The function then increments *i by the length of the content 
string, frees the 
content string, and frees the original value of *str if 
insert_content returned 
a new string. If get_quotes_content returns NULL, the 
function returns without
modifying *str or *i
*/

void	disclose_quotes(char **str, int *i)
{
	char	*content;
	char	*temp;

	content = get_quotes_content(&(*str)[*i]);
	if (!content)
		return ;
	temp = *str;
	*str = insert_content(*str, *i, (*i) + 2 + ft_strlen(content), content);
	(*i) += (int)ft_strlen(content);
	ft_free_strs(temp, content, NULL);
}

/*
EXPAND QUOTES:
This function takes in a string pointer str and iterates through it 
until it reaches the null terminator. If it encounters a single or 
double quote, it calls disclose_quotes with str and the index of 
the quote. Otherwise, it increments the index. The function stops 
iterating if g_info.error is set.
*/

void	expand_quotes(char **str)
{
	int		i;

	i = 0;
	while (!g_info.error && (*str)[i])
	{
		if (ft_strchr("'\"", (*str)[i]))
			disclose_quotes(str, &i);
		else
			i++;
	}
}

/*
DISCLOSE DOLLAR:
This function takes in a string pointer str and an 
integer pointer i, and expands the dollar expansion 
starting at index *i in *str. It does this by calling 
get_dollar_for_expand with the address 
of the character at index *i in *str and using the 
returned string to determine the expansion. If the 
dollar expansion starts with ?, the function sets the 
expansion to the value of g_info.last_prcs. If the dollar 
expansion is a valid.
If the dollar expansion is a valid environment variable, 
the function sets the expansion to the value of the variable. 
If the dollar expansion is not a valid environment variable or 
get_dollar_for_expand returns NULL, the function sets the expansion 
to an empty string. The function then uses insert_content with *str, 
*i, *i + 1 + the length 
of the dollar expansion, and the expansion to create a new string 
and sets *str to it. It then increments *i by the length of the expansion, 
frees the dollar expansion and the expansion string, and frees the 
original value of *str.
*/

void	disclose_dollar(char **str, int *i)
{
	char	*dollar;
	char	*content;
	char	*temp;

	dollar = get_dollar_for_expand(&(*str)[*i]);
	if (!dollar)
		return ;
	if (*dollar == '?')
		content = ft_itoa(g_info.last_prcs);
	else if (ft_getenv(g_info.env, dollar))
		content = ft_strdup(ft_getenv(g_info.env, dollar));
	else if (!ft_isalnum(*dollar))
		content = ft_strjoin("$", dollar);
	else
		content = ft_strdup("");
	if (!content)
	{
		raise_error(MEMORY_ERROR, NULL);
		free(dollar);
		return ;
	}
	temp = *str;
	*str = insert_content(*str, *i, *i + 1 + ft_strlen(dollar), content);
	*i += (int)ft_strlen(content);
	ft_free_strs(temp, dollar, content);
}

/*
EXPAND DOLLAR:
This function takes in a string pointer str and iterates 
through it until it reaches the null terminator. It keeps 
track of whether it is inside double quotes using the 
double_quote boolean variable. If it encounters a single quote 
and is not inside double quotes, it increments the index by the 
result of calling skip_quotes with the address of the character 
at the current index in *str. If it encounters a double quote 
and is not inside double quotes, it sets double_quote to 1. 
If it encounters a double quote and is inside double quotes, 
it sets double_quote to 0. If it encounters a dollar sign that 
is not followed by a space, tab, vertical tab, or null terminator, 
it calls disclose_dollar with str and the index. The function then 
increments the index and stops iterating if g_info.error is set.
*/

void	expand_dollar(char **str)
{
	bool	double_quote;
	int		i;

	i = 0;
	double_quote = 0;
	while (!g_info.error && (*str)[i])
	{
		if ((*str)[i] == '\'' && !double_quote)
			i += skip_quotes(&(*str)[i]);
		else if ((*str)[i] == '"' && !double_quote)
			double_quote = 1;
		else if ((*str)[i] == '"' && double_quote)
			double_quote = 0;
		while ((*str)[i] == '$' && !ft_strchr(" \t\v\0", (*str)[i + 1]))
			disclose_dollar(str, &i);
		i++;
	}
}

/*
EXPAND:
This function takes in a string argument and returns 
a copy of it with any dollar expansions or quoted 
substrings expanded. It does this by first creating 
a copy of argument using ft_strdup and then calling 
expand_dollar and expand_quotes on it. If ft_strdup fails, 
the function sets g_info.error and returns NULL.
*/

char	*expand(char *argument)
{
	char	*new;

	new = ft_strdup(argument);
	if (!new)
		raise_error(MEMORY_ERROR, NULL);
	expand_dollar(&new);
	expand_quotes(&new);
	return (new);
}
