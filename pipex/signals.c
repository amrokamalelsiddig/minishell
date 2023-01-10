/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:37:36 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/10 19:55:25 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
This function handles the signal SIGINT (Ctrl+C) 
by printing a newline character, resetting the readline 
buffer, and setting g_info.last_prcs to 1 and g_info.sig to 1.
*/

void	ft_signal_cltr_c(int sig)
{
	(void) sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_info.last_prcs = 1;
	g_info.sig = 1;
}

/*
This function sets the signal handlers for 
SIGQUIT, SIGTERM, and SIGINT. SIGQUIT and SIGTERM 
are ignored, and SIGINT is handled by ft_signal_cltr_c. 
It also sets g_info.sig to 0.
*/

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c);
	g_info.sig = 0;
}

/*
This function sets the signal handlers for 
SIGTERM, SIGINT, and SIGQUIT in a child process. 
SIGTERM and SIGINT are set to the default signal handler, 
and SIGQUIT is handled by ft_signal_cltr_c.
*/

void	signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, ft_signal_cltr_c);
}

/*
This function handles the signals SIGINT and SIGQUIT by 
ignoring them.
*/

void	ft_signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void) sig;
}

/*
This function sets the signal handlers for SIGINT and 
SIGQUIT to ft_signal_pipes
*/

void	signal_in_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}
