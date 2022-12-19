/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:10:45 by kpanikka          #+#    #+#             */
/*   Updated: 2022/11/08 08:47:16 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(t_msvar *msv)
{
	msv->i = 0;
	ft_putstr_fd("\033[0;31mm", 2);
	if (msv->parse_error == 1)
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		while (msv->rline[msv->i] != ' ' && msv->rline[msv->i] != '\0')
			ft_putchar_fd(msv->rline[msv->i++], 1);
	}
	else if (msv->parse_error == 2)
		ft_putstr_fd("minishell: parse error near ' ", 1);
	else if (msv->parse_error == 3)
		ft_putstr_fd("minishell: parse error near \" ", 1);
	else if (msv->parse_error == 4)
		ft_putstr_fd("minishell:  parse error near `>' ", 1);
	else if (msv->parse_error == 5)
		ft_putstr_fd("minishell:  parse error near `<' ", 1);
	else if (msv->parse_error == 6)
		ft_putstr_fd("minishell:  parse error near `|' ", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("\033[0m", 2);

}

void	clean_exit(t_msvar *msv)
{
	free(msv->rline);
	printf("\n \033[1;34mminishell exited .... \033[0m");
	exit(0);
}
