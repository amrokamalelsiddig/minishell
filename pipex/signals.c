/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:37:36 by hheggy            #+#    #+#             */
/*   Updated: 2022/12/23 13:39:23 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c);
	g_info.sig = 0;
}

void	signal_in_child(void)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, ft_signal_cltr_c);
}

void	ft_signal_pipes(int sig)
{
	signal(SIGINT, SIG_IGN);
	(void) sig;
}

void	signal_in_pipes(void)
{
	signal(SIGINT, ft_signal_pipes);
	signal(SIGQUIT, ft_signal_pipes);
}
