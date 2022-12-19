/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 02:26:13 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/09/03 05:30:22 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*t_dest;
	unsigned char	*t_src;

	i = -1;
	if (!dest && !src)
		return (0);
	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	if (t_src < t_dest && t_dest < t_src + len)
		while (++i < len)
			t_dest[len - 1 - i] = t_src[len - 1 - i];
	else
		while (++i < len)
			t_dest[i] = t_src[i];
	return ((void *)dest);
}
