/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:13:54 by kpanikka          #+#    #+#             */
/*   Updated: 2022/11/07 19:12:56 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_elstnew(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_elstadd_back(t_env **lst, t_env *new)
{
	if (*lst)
		ft_elstlast(*lst)->next = new;
	else
		*lst = new;
}


void	ft_elstadd_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}


int	ft_elstsize(t_env *lst)
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

void	ft_elstclear(t_env **lst)
{
	t_env	*n_lst;

	while (*lst)
	{
		n_lst = *lst;
		*lst = n_lst -> next;
		free(n_lst);
	}
}

t_env	*ft_elstlast(t_env	*lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}