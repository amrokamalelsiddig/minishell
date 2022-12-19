/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:03 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/05 01:21:10 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msvar	msv;

/*
	The function read_loop does a clean exit for the program 
*/

void	init_minishell(t_msvar	*msv)
{
	msv->rline = NULL;
	msv->cmd_num = 0;
	msv->num_pipe = 0;
	msv->quote = 0;
	msv->dquote = 0;
	msv->parse_error = 0;
	msv->w_len = 0;
	msv->w_count = 0;
	msv->exit_flag = 0;
	msv->block_list = NULL;
	// msv->env_list = NULL;
	msv->output = ft_calloc(32767, 1);
	msv->temp = NULL;
	msv->b_temp = NULL;
}

/*
*  The function read_loop  reads line from the command line and then 
*  processes it
* 
*/

int	read_loop(t_msvar *msv)
{
	while (1)
	{
		msv->rline = readline("\033[1;35mminishell $ \033[0m");
		if (msv->rline)
			add_history(msv->rline);
		else
			clean_exit(msv);
		parse(msv);
		if (msv->cmd_num == 7 || msv->exit_flag == 1)
			clean_exit(msv);

		if (!msv->parse_error)
			ft_exec(msv);
		else
			parse_error(msv);
		//ft_dlstprt(msv->block_list); /// check print
		msv->temp = msv->rline;
		free(msv->temp);
		free(msv->output);
		init_minishell(msv);
	}
}

void siginthandler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		msv.exit_flag = 1;
		clean_exit(&msv);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	signal(SIGINT, siginthandler);
	init_minishell(&msv);
	load_env(&msv, env);
	// ft_elstprint(msv.env_list);
	read_loop(&msv);
	return (0);
}
