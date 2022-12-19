/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 04:36:09 by aelsiddi          #+#    #+#             */
/*   Updated: 2022/12/09 04:36:16 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

 /*
** check if the file exist, if not it will creat one 
**
** @param	file name   	
** @return	N/A
*/
void  placefile(char *file_name)
 {
	int fd;

	fd = open(file_name , O_CREAT, 777);
	if (fd == -1)
	{
		fd = open(file_name , O_RDONLY|O_CREAT, 777);
		if (fd == -1)
   		{
			perror("from place file >> Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   		}
	}
	close(fd);
 }

 /*
** overwrite text to an exist file 
**
** @param	file name , text to be written 	
** @return	N/A
*/
 void overwrite(char *file_name, char *str)
 {
	int i;
	int fd;
	char buff;

	fd = open(file_name,O_RDWR|S_IRUSR|S_IWUSR , 777); 

	if (fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while(str[i])
		write(fd,&str[i++],1);
	close(fd);
}
 
 int	ft_strchr(char *str,char c)
{
	int		i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
			return (-1);
		i++;
	}
	return (i);
}

/*
** append text to an exist file 
**
** @param	file name , text to be appended 	
** @return	N/A
*/
void append(char *file_name, char *str)
{
	char buff;
	int fd;
	char holder[256];
	int i;
	int j;
		
	j = 0;
	i = 0;
	fd = open(file_name,O_RDWR , 777);
	if (!(fd))
	{
		perror("Error while opening the file.\n");
      	exit(EXIT_FAILURE);
   	}
	while(read(fd,&buff,1) > 0 && buff != '\0')
		holder[i++] = buff;
	while(str[j])
		holder[j+i] = str[j++];
	j = 0;
	while(str[j])
		write(fd,&str[j++],1);
}

 int main()
 {
	// placefile("mudeer.txt");
	// overwite("mudeer.txt","this is for teoishjgloksjfhkjsting");
	append("mudeer.txt","if passed you should this at the end");
	return 0;
 }