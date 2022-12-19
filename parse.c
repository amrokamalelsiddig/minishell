/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:05:07 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/09 04:13:12 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	parse_split_elements(t_msvar *msv)
{
	while (msv->rline[msv->i++])
	{
		if (msv->parse_error == 1)
			break ;
		if (msv->rline[msv->i] == '\'')
			parse_quote_block(msv);
		else if (msv->rline[msv->i] == '"')
			parse_dquote_block(msv);
		else if (msv->rline[msv->i] == '$')
			parse_dollar_block(msv);
		else if (msv->rline[msv->i] == '>')
			parse_gt_block(msv);
		else if (msv->rline[msv->i] == '<')
			parse_lt_block(msv);
		else if (msv->rline[msv->i] == '|')
			parse_pipe_block(msv);
		else
			parse_nospl_block(msv);
		msv->w_len = 0;
	}
}

/*
	 The function parse_cmd_check checks which 
	 is the command being used .eg : echo , ls etc
*/
void	parse_cmd_check(t_msvar *msv)
{
	msv->temp = msv->block_list->content;
	if (!(ft_strncmp("echo", msv->temp, 4)) && strlen(msv->temp) == 4)
		msv->cmd_num = 1;
	else if (!(ft_strncmp("cd", msv->temp, 2)) && strlen(msv->temp) == 2)
		msv->cmd_num = 2;
	else if (!(ft_strncmp("pwd", msv->temp, 3)) && strlen(msv->temp) == 3)
		msv->cmd_num = 3;
	else if (!(ft_strncmp("export", msv->temp, 6)) && strlen(msv->temp) == 6)
		msv->cmd_num = 4;
	else if (!(ft_strncmp("unset", msv->temp, 5)) && strlen(msv->temp) == 5)
		msv->cmd_num = 5;
	else if (!(ft_strncmp("env", msv->temp, 3)) && strlen(msv->temp) == 3)
		msv->cmd_num = 6;
	else if (!(ft_strncmp("exit", msv->temp, 4)) && strlen(msv->temp) == 4)
		msv->cmd_num = 7;
	else if (validation(msv,msv->temp) == 1)
		msv->cmd_num = 8;
	else
	{
		printf("error from here \n");
		msv->parse_error = 1;
	}
	msv->block_list->cmd_seq = msv->cmd_num;

}

void	parse_cmd_init(t_msvar *msv)
{
	if (msv->parse_error)
		return ;
	if (msv->cmd_num == 1)
		msv->i = 4;
	else if (msv->cmd_num == 2)
		msv->i = 2;
	else if (msv->cmd_num == 3)
		msv->i = 3;
	else if (msv->cmd_num == 4)
		msv->i = 6;
	else if (msv->cmd_num == 5)
		msv->i = 5;
	else if (msv->cmd_num == 6)
		msv->i = 3;
	else if (msv->cmd_num == 8)
		msv->i = 8;
}

void	parse(t_msvar *msv)
{
	msv->temp = ft_get_word(msv->rline, ' ');
	ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 1, 0, 0));
	parse_cmd_check(msv);
	parse_cmd_init(msv);
	parse_split_elements(msv);
}
