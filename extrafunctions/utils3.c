/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:05:08 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 14:06:50 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone1(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

void	ft_lstiter1(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		f(temp->content);
		temp = temp->next;
	}
}

t_list	*ft_lstlast1(t_list *lst)
{
	t_list	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_list	*ft_lstmap1(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*element;

	new = NULL;
	while (lst)
	{
		element = ft_lstnew1((*f)(lst->content));
		if (!element)
		{
			while (new)
				ft_lstclear1(&new, del);
			return (NULL);
		}
		ft_lstadd_back1(&new, element);
		lst = lst->next;
	}
	return (new);
}

t_list	*ft_lstnew1(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list *));
	if (!new)
		return (NULL);
	if (!content)
		new->content = NULL;
	else
		new->content = content;
	new->next = NULL;
	return (new);
}
