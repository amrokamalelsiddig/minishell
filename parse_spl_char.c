/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:13:22 by kpanikka          #+#    #+#             */
/*   Updated: 2022/11/05 16:31:31 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_gt_block(t_msvar *msv)
{
	msv->i++;
	msv->w_len = 1;
	while (msv->rline[msv->i] == '>' && msv->rline[msv->i] != '\0')
	{
		msv->w_len++;
		msv->i++;
	}
	if (msv->w_len == 1)
	{
		msv->temp = ft_strdup(">");
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 0, '>'));
		msv->w_count++;
	}
	else if (msv->w_len == 2)
	{
		msv->temp = ft_strdup(">>");
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 1, '>'));
		msv->w_count++;
	}
	else
		msv->parse_error = 4;
}

void	parse_lt_block(t_msvar *msv)
{
	msv->i++;
	msv->w_len = 1;
	while (msv->rline[msv->i] == '<' && msv->rline[msv->i] != '\0')
	{
		msv->w_len++;
		msv->i++;
	}
	if (msv->w_len == 1)
	{
		msv->temp = ft_strdup("<");
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 0, '<'));
		msv->w_count++;
	}
	else if (msv->w_len == 2)
	{
		msv->temp = ft_strdup("<<");
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 1, '<'));
		msv->w_count++;
	}
	else
		msv->parse_error = 5;
}

void	parse_pipe_block(t_msvar *msv)
{
	msv->i++;
	msv->w_len = 1;
	while (msv->rline[msv->i] == '|' && msv->rline[msv->i] != '\0')
	{
		msv->w_len++;
		msv->i++;
	}
	if (msv->w_len == 1)
	{
		msv->temp = ft_strdup("|");
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 0, '|'));
		msv->w_count++;
	}
	else if (msv->w_len == 2)
	{
		msv->temp = ft_strdup("||");
		ft_dlstadd_back(&msv->block_list, ft_dlstnew(msv->temp, 0, 1, '|'));
		msv->w_count++;
	}
	else
		msv->parse_error = 6;
}
