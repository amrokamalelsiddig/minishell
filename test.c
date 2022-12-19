/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:51:46 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/05 03:33:27 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>

 void ft_exce_other(char **argv, pid_t par_pid)
 {
	int v;
	int pid;
	int acc;


	acc = access(argv[0],X_OK);
	
	printf("acc is : %i\n",acc);
	if (acc == 0)
	{
		v = execve(argv[0],argv,NULL);; 
		if (v ==  -1)
		{
			perror("\033[0;31m");
		}
	}
 }
	
 int main(int ac, char **av, char **env)
 {
	//str join between /bin/ and 1st agenemt to wite the bath and place 2ed args parms for
	pid_t pid;

	pid = getpid();
	char *argv[] = {"/bin/ls","-l",NULL};
	ft_exce_other(argv,pid);
	return 0;
 }