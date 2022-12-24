/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:37:17 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/24 10:37:18 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd1(void)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
	{
		g_info.error = errno;
		return (1);
	}
	ft_putendl_fd(temp, 1);
	free(temp);
	return (0);
}
