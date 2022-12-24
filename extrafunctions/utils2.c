/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:01:52 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 14:04:55 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_strs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr("-+", *str))
		str++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 19 || ft_atoul(str) > 9223372036854775807)
		return (0);
	return (1);
}

void	ft_lstadd_back1(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		;
	else if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_lstadd_front1(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstclear1(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *lst;
	while (temp != NULL)
	{
		temp2 = temp->next;
		del(temp->content);
		free(temp);
		temp = temp2;
	}
	*lst = NULL;
}
