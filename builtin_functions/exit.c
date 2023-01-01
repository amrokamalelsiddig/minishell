/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 10:36:57 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/24 21:08:24 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_success(void)
{
	if (!g_info.commands->next)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
		return (0);
}

int	exit_num(char *argv)
{
	u_int64_t	code;

	code = ft_atoul(argv);
	if (!g_info.commands->next)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit((unsigned char) code);
	}
	else
		return ((unsigned char) code);
}

int	arg_error(void)
{
	if (!g_info.commands->next)
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putendl_fd(ARG_ERROR, STDERR_FILENO);
	return (1);
}

int	num_error(char *argv)
{
	if (!g_info.commands->next)
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(NUM_ERROR, STDERR_FILENO);
	if (!g_info.commands->next)
		exit(255);
	return (255);
}

int	ft_exit(char **argv)
{
	if (argv && argv[1])
	{
		if (!ft_isnumeric(argv[1]))
			return (num_error(argv[1]));
		else if (argv[2])
			return (arg_error());
		else
			return (exit_num(argv[1]));
	}
	return (exit_success());
}
