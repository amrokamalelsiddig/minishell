/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:29:56 by kpanikka          #+#    #+#             */
/*   Updated: 2022/11/06 12:51:37 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_get_word(char *str, char ch)
{
	int	i;

	i = ft_strchr(str, ch) - str;
	return (ft_substr(str, 0, i));
}
// void	ft_putchar_fd(char c,int fd)
// {
// 	write(1, &c, fd);
// }

// void	ft_putnbr_fd(int n, int fd)
// {
// 	unsigned int	num;

// 	num = n;
// 	if (n < 0)
// 	{
// 		write(1, "-", fd);
// 		num = -n;
// 	}
// 	if (num >= 10)
// 		ft_putnbr_fd(num / 10, 1);
// 	ft_putchar_fd(num % 10 + '0', 1);
// }

// void	ft_putstr_fd(char *s,int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return ;
// 	while (s[i])
// 	{
// 		write(1, &s[i], fd);
// 		i++;
// 	}
// 	write(1, "\n", fd);
// }


// int	ft_atoi(const char *str)
// {
// 	int				i;
// 	int				sign;
// 	unsigned int	num;

// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
// 		|| str[i] == '\n' || str[i] == '\f')
// 		i++;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 		num = num * 10 + str[i++] - '0';
// 	if (num >= 2147483648 && sign == 1)
// 		return (-1);
// 	else if (num > 2147483648 && sign == -1)
// 		return (0);
// 	else
// 		return (num * sign);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	if (!s1 || !s2)
// 		return (0);
// 	i = ft_strlen(s1);
// 	j = ft_strlen(s2);
// 	str = (char *) ft_calloc(i + j + 1, sizeof(*s1));
// 	if (!str)
// 		return (NULL);
// 	ft_memcpy(str, s1, i);
// 	ft_memcpy(str + i, s2, j);
// 	return (str);
// }