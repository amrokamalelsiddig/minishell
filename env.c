/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:51:05 by kpanikka          #+#    #+#             */
/*   Updated: 2022/11/07 19:13:11 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_env(t_msvar *msv, char **env)
{
	int		i;
	char	*value;
	char	*temp;
	t_env	*env_lst;

	i = 0;
	while (env[i])
	{
		temp = ft_get_word(env[i], '=');
		value = ft_strdup(env[i] + ft_strlen(temp) + 1);
		env_lst = ft_elstnew(temp, value);
		if (env_lst)
			ft_elstadd_back(&msv->env_list, env_lst);
		else
			clean_exit(msv);
		i++;
	}
}

/*
*	Accept the string to check in the environment variable and 
	returns the value if key exists
*/
char	*ft_getenv(char *str, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(str, env_list->key, 32767) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}



int	ft_elstprint(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("%s = %s\n", lst->key, lst->value);
		lst = lst->next;
		i++;
	}
	return (i);
}