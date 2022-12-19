/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:09:38 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/04 22:33:51 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_exec_echo_q(t_dlist *temp)
{
	//(void)temp;
	ft_putstr_fd(temp->content, 1);
	//ft_putchar_fd('\n', 1);
	return ;
}


void	ft_exec_echo_dq(t_dlist *temp, t_msvar *msv)
{		
	int	i;

	i = 0;
	while (temp->content[i])
	{
		if (temp->content[i] == '$')
			ft_putstr_fd(ft_getenv(temp->content + 1, msv->env_list), 1);
		else
			ft_putchar_fd(temp->content[i], 1);
		i++;
	}
	return ;
}

void	ft_exec_echo(t_msvar *msv)
{
	t_dlist	*temp;

	temp = msv->block_list->next;
	if (temp->quote == '\'')
		ft_exec_echo_q(temp);
	else if (temp->quote == '\"')
		ft_exec_echo_dq(temp, msv);
	else
		ft_putstr_fd(temp->content,1);
	//ft_putstr_fd(msv->rline+5, 1);
	ft_putchar_fd('\n', 1);
}
