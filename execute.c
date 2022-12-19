/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:42:15 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/05 01:01:45 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_msvar *msv)
{
	printf("cmd_seq : %d\n", msv->block_list->cmd_seq);
	if (msv->block_list->cmd_seq == 1)
		ft_exec_echo(msv);
	else if (msv->block_list->cmd_seq == 2)
		ft_exec_cd(msv);
	else if (msv->block_list->cmd_seq == 3)
		ft_exec_pwd(msv);
	else if (msv->block_list->cmd_seq == 4)
		ft_exec_export(msv);
	// else if (msv->block_list->cmd_seq == 5)
	// 	ft_exec_unset(msv);
	else if (msv->block_list->cmd_seq == 6)
		ft_exec_env(msv);
	else if (msv->block_list->cmd_seq == 8)
		handle_other(msv);
}
