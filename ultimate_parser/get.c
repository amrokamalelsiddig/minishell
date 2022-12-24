/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:49:22 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 13:49:24 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
