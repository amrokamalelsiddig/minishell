/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:31:04 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/09/03 05:29:55 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstmap(t_node *lst, int (*f)(void *), void (*del)(void *))
{
	t_node	*result;
	t_node	*temp;

	result = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = ft_lstnew(f(lst->link));
		if (!temp)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&result, temp);
		}
		lst = lst->link;
	}
	return (result);
}

// if (!lst || !del)
// 		return (NULL);
// {
// 	t_list	*result;

// 	result = (t_list *)malloc(ft_lstsize(lst) * sizeof(t_list));
// 	if (!result)
// 		return (NULL);
// 	while (lst)
// 	{
// 		if (!(lst->content))
// 		{
// 			result = f(lst->content);
// 			lst = lst->next;
// 			result = result->next;
// 		}
// 		else
// 		{
// 			del(lst->content);
// 			result = f(lst->content);
// 			lst = lst->next;
// 			result = result->next;
// 		}
// 	}
// 	return (result);
// }
