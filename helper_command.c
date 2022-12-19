/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:51:25 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/19 19:56:41 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validation(t_msvar *msv, char *opt_arg)
{
	t_env 	*tmp;
	char 	**path;
	int 	i;
	
	i = 0;
	tmp = msv->env_list;
	while(tmp)
	{
		if (!(strncmp("PATH",tmp->key,4)))
		{
			path = ft_split(tmp->value,':');
			break;	
		}
		tmp = tmp->next;
	}
	while(path[i++])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], msv->temp);
		if((access(path[i], X_OK)) == 0)
		{
			msv->path = path[i];
			return (1);
		}
	}
	char *test = opt_arg;
	free(test);
	return (0);
}


void handle_other(t_msvar *msv)
{
	int 	acc;
	int 	v;
	int 	pid;
	// char **agrument;

	//agrument[1] =  optional argument should go here **///
	pid = fork();
	if(pid < 0)
	{
		perror("\033[0;31m");
		exit(0);
	}
	acc = access(msv->path,X_OK);	
	printf("acc is : %i\n",acc);
	waitpid(pid, NULL,0);	
	if (acc == 0 && pid == 0)
	{
		v = execve(msv->path,&(msv->block_list->content),NULL);; 
		if (v ==  -1)
			perror("\033[0;31m");
	}
 }