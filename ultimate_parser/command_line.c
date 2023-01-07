/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:48:32 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 13:46:34 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
ADD ARGUMENT:
This function takes in a string pointer str and a pointer 
to a linked list list. 
It creates a new element for the linked list by calling 
ft_lstnew1 with a string 
obtained from get_argument(*str). The function then adds 
this new element to the end of list using ft_lstadd_back1, 
and increments str by the length of the argument string. 
If get_argument returns NULL or if there is a memory allocation error, 
the function returns without modifying list.
*/
void	add_argument(char **str, t_list **list)
{
	t_list	*new;
	char	*argument;

	argument = get_argument(*str);
	if (!argument)
		return ;
	new = ft_lstnew1(argument);
	if (!new)
	{
		free(argument);
		raise_error(MEMORY_ERROR, NULL);
		return ;
	}
	ft_lstadd_back1(list, new);
	*str += ft_strlen(argument);
}

/*
ADD REDIRECT:
This function is similar to add_argument, 
but it calls get_redirect instead of get_argument 
to obtain the string for the new linked list element. 
It also increments str by the value returned by 
skip_redirect(*str) rather than the length of the redirect string.
*/

void	add_redirect(char **str, t_list **list)
{
	t_list	*new;
	char	*redirect;

	redirect = get_redirect(*str);
	if (!redirect)
		return ;
	new = ft_lstnew1(redirect);
	if (!new)
	{
		free(redirect);
		raise_error(MEMORY_ERROR, NULL);
		return ;
	}
	ft_lstadd_back1(list, new);
	*str += skip_redirect(*str);
}

/*
ADD DOLLAR:
This function takes in a string pointer str and a pointer to a 
linked list list. It creates a new element for the linked list 
by calling ft_lstnew1 with a string obtained 
from get_dollar_for_expand(*str). 
If the string returned by get_dollar_for_expand starts with ?, 
is an empty string,
or is a valid environment variable, 
the function adds the new element to the end of list using ft_lstadd_back1. 
Otherwise, it increments str by the length of the dollar string plus 1. 
The function frees the dollar string regardless of the outcome.
*/

void	add_dollar(char **str, t_list **list)
{
	t_list	*new;
	char	*dollar;

	new = NULL;
	dollar = get_dollar_for_expand(*str);
	if (!dollar)
		return ;
	if (*dollar == '?' || *dollar == '\0'
		|| ft_getenv(g_info.env, dollar))
	{
		new = ft_lstnew1(get_argument(*str));
		if (!new)
		{
			free(dollar);
			raise_error(MEMORY_ERROR, NULL);
			return ;
		}
		*str += ft_strlen(new->content);
		ft_lstadd_back1(list, new);
	}
	else
		*str += ft_strlen(dollar) + 1;
	free(dollar);
}

/*
SPLIT COMMAND LINE:
This function takes in a string str and an array of two pointers 
to linked lists list. It initializes both elements of list to NULL. 
The function then iterates through str and performs one of the following 
actions for each character:

If the character is a whitespace, the function increments str.
If the character is < or >, the function calls add_redirect with str 
and the second element of list.
If the character is $ and the next character is alphanumeric, 
the function calls add_dollar with str and the first element of list.
Otherwise, the function calls add_argument with str and the 
first element of list.
The function continues until it encounters a | character or 
the null terminator, or until g_info.error is set.
*/

void	split_command_line(char *str, t_list *list[2])
{
	list[0] = NULL;
	list[1] = NULL;
	while (!ft_strchr("|\0", *str) && !g_info.error)
	{
		if (ft_strchr(" \t\v", *str))
			str++;
		else if (ft_strchr("<>", *str))
			add_redirect(&str, &list[1]);
		else if (*str == '$' && ft_isalnum(str[1]))
			add_dollar(&str, &list[0]);
		else
			add_argument(&str, &list[0]);
	}
}

/*
GET COMMAND LINE:
This function takes in a string pointer str and 
returns a substring of *str delimited by the next | 
character or the null terminator. 
The function increments *str as it iterates through 
the returned string, skipping over any quoted substrings 
it encounters. If *str starts with a | character, 
the function increments *str before returning.
*/

char	*get_command_line(char **str)
{
	char	*command_line;

	command_line = *str;
	while (**str && **str != '|' && !g_info.error)
	{
		if (ft_strchr("'\"", **str))
			(*str) += skip_quotes(*str);
		(*str)++;
	}
	if (**str == '|')
		(*str)++;
	return (command_line);
}
