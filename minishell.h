/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:36 by kpanikka          #+#    #+#             */
/*   Updated: 2022/12/09 04:13:23 by aelsiddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*
* ! The struct s_dlist is a doubly linked list
	content is the data stored in the node
	next is the pointer to the next node
	prev is the pointer to the previous node
		len_quote is the length of the quote used for >> or << redirection 
	it will be 1 else for all it is 0
	cmd_seq is the command sequence number for the command 0 for no command 
		1 for first command 2 for second command and 
		so on till command 7 for exit
		after 7 the program will check if the command is there in the system  
		and then execute it or give an error
	is_opti is a flag to check if the command is a option or not
*/

typedef struct s_dlist
{
	char			*content;
	char			quote;
	int				len_quote;
	int				cmd_seq;
	int				is_option;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

/*
	cmd_num is the number to find which command 
	eg echo = 1 
		...
*/
typedef struct minishellvariables
{
	char	*rline;
	int		i;
	char	*output;
	int		cmd_num;
	int		quote;
	int		dquote;
	int		num_pipe;
	int		parse_error;
	int		exit_flag;
	int		w_count;
	int		w_len;
	t_dlist	*block_list;
	t_env	*env_list;	
	char	*temp;
	char	*b_temp;
	char    *path;
}t_msvar;

void	parse(t_msvar *msv);
void	parse_error(t_msvar *msv);
void	parse_gt_block(t_msvar *msv);
void	parse_lt_block(t_msvar *msv);
void	parse_pipe_block(t_msvar *msv);
void	parse_quote_block(t_msvar *msv);
void	parse_dquote_block(t_msvar *msv);
char	*parse_dollar_block(t_msvar *msv);
void	parse_nospl_block(t_msvar *msv);

void	load_env(t_msvar *msv, char **env);
char	*ft_getenv(char *str, t_env *env_list);

void	clean_exit(t_msvar *msv);
// void	ft_exec(t_msvar *msv);
void	ft_exec(t_msvar *msv);
void	ft_exec_echo(t_msvar *msv);

t_dlist	*ft_dlstnew(char *data, int cmd_seq, int len_q, char q);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
int		ft_dlstsize(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
int		ft_dlstprt(t_dlist *lst);

t_env	*ft_elstnew(char *key, char *value);
void	ft_elstadd_back(t_env **lst, t_env *new);
void	ft_elstadd_front(t_env **lst, t_env *new);
int		ft_elstsize(t_env *lst);
void	ft_elstclear(t_env **lst);
t_env	*ft_elstlast(t_env *lst);
int		ft_elstprint(t_env *lst);

char	*ft_get_word(char *str, char ch);

void 	ft_exec_pwd(t_msvar *lst);
void 	ft_exec_env(t_msvar *lst);
void 	ft_exec_exit();
// void ft_exec_cd(t_msvar *lst);
void 	ft_exec_cd(t_msvar *lst);
char	*ft_substr2(char *s, unsigned int start, size_t	len);

//*****************dir.c**************//
int getDirList(char *str);
int ls(t_msvar *lst);

//***********export.c****************//
void	ft_exec_export(t_msvar *lst);

//*********helper_command.c**********//
void	handle_other(t_msvar *msv);
int 	validation(t_msvar *msv, char *opt_arg);
#endif