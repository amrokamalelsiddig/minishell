/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:13:54 by kpanikka          #+#    #+#             */
/*   Updated: 2022/11/07 22:41:23 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*ft_dlstnew(char *data, int cmd_seq, int len_q, char q)
{
	t_dlist	*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->content = data;
	new->cmd_seq = cmd_seq;
	new->len_quote = len_q;
	new->quote = q;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	if (*lst)
	{
		new->prev = ft_dlstlast(*lst);
		ft_dlstlast(*lst)->next = new;
	}
	else
		*lst = new;
}

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (*lst)
		(*lst)->prev = new;
	new->next = *lst;
	new -> prev = NULL;
	*lst = new;
}

int	ft_dlstprt(t_dlist *lst)
{
	int	i;

	i = 0;
			lst = lst->next;

	while (lst)
	{
		//printf("content: %s, cmd_seq: %d, len_quote: %d, quote: %c\n", lst->content, lst->cmd_seq, lst->len_quote, lst->quote);
		printf("%s ", lst->content);
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_dlstsize(t_dlist *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
void	ft_dlstclear(t_dlist **lst)
{
	t_dlist	*n_lst;

	while (*lst)
	{
		n_lst = *lst;
		*lst = n_lst -> next;
		free(n_lst);
	}
}

t_dlist	*ft_dlstlast(t_dlist	*lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}