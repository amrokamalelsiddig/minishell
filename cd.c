/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 04:15:03 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/02 04:20:03 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_cd(t_msvar *lst)
{
	t_msvar *temp;
	t_env *temp2;
	// DIR *dp;
    // struct dirent *dirp;
	temp = lst;
	temp2 =  lst->env_list;
	char *holder = ft_substr2(temp->rline,3,(ft_strlen(temp->rline)-3));
	if(!(ft_strncmp(holder ,"..",ft_strlen(holder))))
		printf("This  should be replaced with root dir\n");
	if (!(getDirList(holder)))
	{
		ft_putstr_fd("cd: no such file or directory: ",1);
		ft_putstr_fd(holder,1);
		printf("\n");
		return;
	}
	while(temp2)
	{
		if(!(strncmp("PWD",temp2->key,3)))
		{
			temp2->value = ft_strjoin(temp2->value,"/");
			temp2->value = ft_strjoin(temp2->value,holder);
		}
		temp2 = temp2->next;
	}
	ft_exec_pwd(lst);
}


