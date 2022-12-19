#include "minishell.h"

int getDirList(char *str)
{
    DIR *dp;
    struct dirent *dirp;


    if (!(str)) 
    {
        fprintf(stderr, "Usage: ./program directory_name\n");
        return(0);
    }
    dp = opendir(str);
    if (!(dp))
        return 0;
    while ((dirp = readdir(dp)) != NULL)
        if (!(strncmp(str,dirp->d_name,ft_strlen(str))))
        {
            printf("found\n");
            return 1;
        }
    closedir(dp);
    return 0;
}

int ls(t_msvar *lst)
{
    char  **holder;
   	t_env *temp;
	int i =0;
	temp = lst->env_list;
	while(temp)
	{
		if(!(strncmp("PWD",temp->key,3)))
			holder = ft_split(temp->value,'/');
		temp = temp->next;
	}
    while (holder[i++])
    {
        printf("%s\t",holder[i]);
    }
    
    return 1;
}

