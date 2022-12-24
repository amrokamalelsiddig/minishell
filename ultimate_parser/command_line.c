/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:48:32 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 13:48:34 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
