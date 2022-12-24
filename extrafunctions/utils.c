/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:00:30 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 14:01:18 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*freedom(char ***arr)
{
	char	**temp;

	temp = *arr;
	while (temp)
	{
		free(*temp);
		temp += sizeof(char *);
	}
	free(*arr);
	return (NULL);
}

char	**ft_arrdup(char **arr, int add)
{
	char	**temp;
	int		index;
	int		counter;

	index = 0;
	counter = 0;
	while (arr[counter])
		counter++;
	temp = ft_calloc(counter + add + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	while (index < counter)
	{
		temp[index] = ft_strdup(arr[index]);
		if (!temp[index])
			return (freedom(&temp));
		index++;
	}
	return (temp);
}

int	ft_arrlen(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

uint64_t	ft_atoul(const char *str)
{
	uint64_t	nbr;
	int			dgt;

	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		dgt = *str++ - 48;
		nbr += dgt;
	}
	return (nbr);
}

void	*free_arr(char ***arr)
{
	char	**temp;
	int		index;

	index = 0;
	temp = *arr;
	if (!temp)
		return (temp);
	while (temp[index])
	{
		free(temp[index]);
		temp[index] = NULL;
		index++;
	}
	free(temp);
	temp = NULL;
	return (NULL);
}
