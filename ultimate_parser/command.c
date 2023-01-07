/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:48:49 by hheggy            #+#    #+#             */
/*   Updated: 2023/01/07 13:50:45 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
FREE COMMAND:
This function takes in a pointer to a t_command 
structure and frees the memory associated with it 
and all subsequent 
t_command structures in a linked list. 
It does this by iterating through the linked list 
and freeing the memory of each element's name, argv, 
rdrct, file, and t_command structure before setting 
command to the next element in the list.
*/

void	*free_command(t_command *command)
{
	t_command	*temp;

	while (command)
	{
		temp = command;
		command = command->next;
		if (temp->name)
			free(temp->name);
		if (temp->argv)
			free_arr(&temp->argv);
		if (temp->rdrct)
			free_arr(&temp->rdrct);
		if (temp->file)
			free(temp->file);
		free(temp);
	}
	return (NULL);
}

/*
FROM LIST TO ARRAY:
This function takes in a pointer to a linked list 
and returns an array of strings obtained by expanding 
each element's content using expand and null-terminating the array. 
The function first allocates memory for the array and then iterates 
through the linked list, assigning each element's expanded content 
to an element in the array. If memory allocation fails, 
the function returns NULL
*/

char	**from_list_to_array(t_list *list)
{
	char	**array;
	int		index;
	t_list	*temp;

	array = malloc(sizeof(char *) * (ft_lstsize1(list) + 1));
	if (!array)
		return (NULL);
	index = 0;
	temp = list;
	while (temp)
	{
		array[index++] = expand(temp->content);
		temp = temp->next;
	}
	array[index] = NULL;
	return (array);
}

/*
NEW COMMAND:
This function takes in an array of two pointers to linked lists 
list and returns a pointer to a t_command structure initialized 
with the expanded contents of list. The function first allocates 
memory for the structure and then sets its argv and rdrct fields 
to the arrays obtained by calling from_list_to_array on the two 
linked lists. It then sets the name field to the result of appending 
the first element of argv to the appropriate directory in PATH. The 
file field is set to NULL and the next field is set to NULL. If memory 
allocation fails at any point, the function sets g_info.error and 
returns NULL
*/

t_command	*new_command(t_list *list[2])
{
	t_command	*command;
	char		**path;

	command = malloc(sizeof(t_command));
	if (!command)
		return (raise_error(MEMORY_ERROR, NULL));
	command->argv = from_list_to_array(list[0]);
	command->rdrct = from_list_to_array(list[1]);
	if (!command->argv || !command->rdrct)
		return (raise_error(MEMORY_ERROR, NULL));
	path = get_split_path();
	command->name = add_full_path(ft_strdup(command->argv[0]), path);
	command->file = NULL;
	command->next = NULL;
	free_arr(&path);
	return (command);
}

/*
GET LAST COMMAND:
 This function takes in a pointer to a t_command structure 
 and returns a pointer to the last t_command structure in 
 the linked list. It does this by iterating through the linked 
 list until it reaches the element whose next field is NULL.
*/

t_command	*get_last_command(t_command *command)
{
	t_command	*last;

	last = command;
	while (last->next)
		last = last->next;
	return (last);
}

/*
ADD NEW COMMAND:
This function takes in a double pointer to a t_command 
structure command and an array of two pointers to linked lists list. 
If *command is NULL, the function sets *command to the result of 
calling new_command with list. Otherwise, it sets the next field 
of the last element in the linked list pointed to by *command to 
the result of calling new_command with list.
*/

void	*add_new_command(t_command **command, t_list *list[2])
{
	t_command	*last;

	if (!*command)
		*command = new_command(list);
	else
	{
		last = get_last_command(*command);
		last->next = new_command(list);
	}
	return (NULL);
}
