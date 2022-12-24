/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:08:24 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 14:09:45 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize1(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		if (temp->next == NULL)
			return (i);
		temp = temp->next;
	}
	return (i);
}

char	*ft_strcut(char *str, char *set)
{
	char	*new;
	int		i;

	if (!str || !set)
		return (NULL);
	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*new;
	size_t	len;
	size_t	index;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (n > len)
		n = len;
	new = malloc(sizeof (char) * (n + 1));
	if (!new)
		return (NULL);
	index = 0;
	while (index < n)
	{
		new[index] = s1[index];
		index++;
	}
	new[index] = '\0';
	return (new);
}
