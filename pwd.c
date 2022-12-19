/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:44:56 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/02 04:15:00 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr2(char *s, unsigned int start, size_t	len)
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


void ft_exec_pwd(t_msvar *lst)
{
	t_env *temp;
	
	temp = lst->env_list;
	while(temp)
	{
		if(!(strncmp("PWD",temp->key,3)))
			ft_putstr_fd(temp->value,1);
		temp = temp->next;
	}
	ft_putchar_fd('\n',1);
	free(temp);
}

void ft_exec_env(t_msvar *lst)
{
	t_env *temp;
	
	temp = lst->env_list;
	while(temp)
	{
		ft_putstr_fd(temp->key,1);
		ft_putchar_fd('=',1);
		ft_putstr_fd(temp->value,1);
		ft_putchar_fd('\n',1);
		temp = temp->next;
	}
	// free(temp);
}

void ft_exec_exit()
{
	exit(3);
}

