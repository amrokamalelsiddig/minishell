/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 04:05:03 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/11 05:55:07 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	int fd[3][2];
	int f1,f2;
	char *argv[] = {"/bin/cat",NULL,NULL};
	char *argv1[] = {"/bin/grep","42",NULL};
	char *argv2[] = {"/bin/wc","-l",NULL};
	f1=open("mudeer.txt",O_RDONLY,777);
	if(f1==-1)
		perror("error1:");
	f2=open("abc.txt",O_RDONLY|O_CREAT|O_RDWR, 777);
	if(f2==-1)
		perror("error2:");
	int i =0;
	while(i<3)
	{
		if (pipe(fd[i]) == -1)
		{
			printf("An error while forking\n");
			return 1;	
		}
	int j=(int) i-1;
	int id = fork();
	if (id == 0)
	{
		if(i==0)
			dup2(f1,0);
		else
			dup2(fd[j][0],0);		
		if(i< 2)
			dup2(fd[i][1],1);
		else
			dup2(f2,1);
		if(i == 0)
			execve(argv[0],argv,NULL);
		else if(i == 1)
			execve(argv1[0],argv1,NULL);
		else if(i == 2)
			execve(argv2[0],argv2,NULL);		
	}
	if(i!=0)
	close(fd[j][0]);
	close(fd[i][1]);
	i++;
	}
	return 0;
}

