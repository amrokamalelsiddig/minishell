/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 08:43:03 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/09/03 05:31:53 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const	*s, unsigned int start, size_t	len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || len < 1)
		str = (char *)malloc(sizeof(*s));
	else if (ft_strlen(s) - start < len)
		str = (char *)malloc((ft_strlen(s) - start + 1) * sizeof(*s));
	else
		str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

// {
// 	char			*result;
// 	size_t			i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s) < start || len < 1)
// 		return ((char *)ft_calloc(1, sizeof(char *)));
// 	else if (ft_strlen(s) - start < len)
// 		result = (char *)ft_calloc(ft_strlen(s) - start + 1, sizeof(char *));
// 	else
// 		result = (char *)ft_calloc(len + 1, sizeof(char *));
// 	if (!result)
// 		return (0);
// 	while (s[i + start] && i < len)
// 	{
// 		result[i] = s[i + start];
// 		i++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }
