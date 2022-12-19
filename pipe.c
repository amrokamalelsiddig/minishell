/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 05:56:52 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/11 06:41:36 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_path
{
	char			*ls;
	char			*grep;
	char			*wc;
	char			*cmd;
}	t_path;

void init_pipe(t_path *pt)
{
	pt->ls[0] = "ls";	
	pt->ls[1] = NULL;	


	// ls[0] = "ls";
	// ls[1] = NULL;
	
	// grep[0] ="grep";
	// grep[1] ="pipe";
	// grep[2] = NULL;
	
	// wc[0] = "wc";
	// wc[1] = NULL;
	
  	// cmd[0] = ls;
  	// cmd[1] = grep;
  	// cmd[2] = wc;
  	// cmd[3] = NULL;
	
	return (cmd);
}

int main()
{
	char ***test = init_pipe();
	int j =0;
	int i=0;
	while(test[i])
	{
		printf("%s",test[i][j]);
		i++;
		j++;
	}
	return 0;
}
