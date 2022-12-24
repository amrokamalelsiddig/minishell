/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:52:58 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 13:53:00 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
