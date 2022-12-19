/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 12:53:28 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/09/03 05:29:34 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_node **lst, void (*del)(void*))
{
	t_node	*temp;

	if (!lst)
		return ;
	temp = *lst;
	while (temp)
	{
		temp = (*lst)->link;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	lst = 0;
}
