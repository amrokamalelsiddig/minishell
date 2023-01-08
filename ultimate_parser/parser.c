/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:52:58 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/08 14:39:30 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
CHECK CORRECT USE OF PIPES:
This function takes a string str and checks 
if the pipes (| characters) in the string are 
used correctly. The function sets the global error 
flag if the pipes are used incorrectly.
*/

void	check_correct_use_of_pipes(char *str)
{
	bool	word;
	bool	pipe;

	word = 0;
	pipe = 0;
	while (*str && !g_info.error)
	{
		if (*str == '|')
		{
			if (!word || str[1] == '|')
				raise_error(TOKEN_ERROR, str);
			pipe = 1;
			word = 0;
		}
		else if (!ft_strchr(" \t\v", *str))
		{
			if (*str == '\'' || *str == '"')
				str += skip_quotes(str);
			word = 1;
		}
		str++;
	}
	if (pipe == 1 && word == 0 && !g_info.error)
		raise_error(NEWL_ERROR, NULL);
}

/*
STR IS EMPTY:
This function takes a string str and 
returns 1 if the string only consists of 
whitespace characters, and 0 otherwise
*/

int	str_is_empty(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!ft_strchr(" \t\v", str[index]))
			return (0);
		index++;
	}
	return (1);
}

/*
PARSE STRING:
This function takes a string str and parses 
it into a linked list of t_command structs, 
each representing a command and its arguments. 
The function returns a pointer to the first element 
of the linked list. If an error occurs during parsing, 
the function frees the linked list and returns NULL.
*/

t_command	*parse_string(char *str)
{
	t_command	*command;
	char		*command_line;
	t_list		*list[2];

	g_info.error = 0;
	command = NULL;
	if (str_is_empty(str))
		return (NULL);
	check_correct_use_of_pipes(str);
	while (*str && !g_info.error)
	{
		command_line = get_command_line(&str);
		split_command_line(command_line, list);
		add_new_command(&command, list);
		ft_lstclear1(&list[0], free);
		ft_lstclear1(&list[1], free);
	}
	if (g_info.error)
		return (free_command(command));
	return (command);
}
