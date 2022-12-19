/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 06:34:47 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/09/03 05:29:25 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_node	**alst, t_node	*new)
{
	if (!alst)
		return ;
	new->link = *alst;
	*alst = new;
	ft_lstlast(*alst)->link = NULL;
}
