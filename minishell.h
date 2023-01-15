/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:12:36 by kpanikka          #+#    #+#             */
/*   Updated: 2023/01/10 20:00:18 by hheggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <err.h>
# include <stdbool.h>
# include <inttypes.h>

# define INPUT_END 1
# define OUTPUT_END 0
# define NO_FILE -1
# define NO_READ -2
# define NO_WRIT -3
# define MEM_ERR -4
# define OPN_ERR -5
# define HEREDOC 100
# define SIG_END 130
# define SIG_BCK 131
# define STD_VAL 200
# define NONBLTN 1000
# define MEMORY_ERROR "minishell: Cannot allocate memory"
# define TOKEN_ERROR "minishell: syntax error near unexpected token "
# define NEWL_ERROR "minishell: syntax error near unexpected token `newline'"
# define ARG_ERROR "too many arguments"
# define NUM_ERROR "numeric argument required"
# define COMMAND_ERROR "\033[0;31mminishell: command not found:\n"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	int		fd_redirs[2];
	int		num;
	char	*file;
	char	*name;
	char	**argv;
	char	**rdrct;
	pid_t	pid;
	void	*next;
	int		error_code;
}			t_command;

typedef struct s_info
{
	uint8_t		sig;
	uint8_t		error;
	int			last_prcs;
	int32_t		std_fd[2];
	int32_t		*filed;
	t_command	*commands;
	char		*minidir;
	char		**files;
	char		**env;
	char		**bltn;
}				t_info;

extern t_info	g_info;

/////************ NEW PARSING FUNCTIONS *******//////////
void		error(char *str, int err);
char		*ft_getenv(char **envp, char *name);
int			skip_argument(char *str);
int			skip_quotes(char *str);
int			skip_redirect(char *str);
void		check_correct_use_of_pipes(char *str);
int			str_is_empty(char *str);
t_command	*parse_string(char *str);
char		**get_split_path(void);
char		*insert_content(char *str, int start, int end, char *content);
void		*raise_error(char *message, char *str);
int			is_builtin_command(char *name);
char		*add_full_path(char *str, char **path);
char		*get_quotes_content(char *str);
char		*get_dollar(char *str);
char		*get_dollar_for_expand(char *str);
char		*get_redirect(char *str);
char		*get_argument(char *str);
void		disclose_quotes(char **str, int *i);
void		expand_quotes(char **str);
void		disclose_dollar(char **str, int *i);
void		expand_dollar(char **str);
char		*expand(char *argument);
void		*free_command(t_command *command);
char		**from_list_to_array(t_list *list);
t_command	*new_command(t_list *list[2]);
t_command	*get_last_command(t_command *command);
void		*add_new_command(t_command **command, t_list *list[2]);
void		add_argument(char **str, t_list **list);
void		add_redirect(char **str, t_list **list);
void		add_dollar(char **str, t_list **list);
void		split_command_line(char *str, t_list *list[2]);
char		*get_command_line(char **str);
int			command_center(char *input, char ***envp);
int			get_exit(t_command *commands);
void		print_msg(int *stat);
/////************ NEW PARSING FUNCTIONS *******//////////

//////////////////******* EXTRA FUNCTIONS FROM LIBFT /////////////////////
void		ft_lstadd_back1(t_list **lst, t_list *new);
void		ft_lstadd_front1(t_list **lst, t_list *new);
void		ft_lstclear1(t_list **lst, void (*del)(void*));
void		ft_lstdelone1(t_list *lst, void (*del)(void*));
void		ft_lstiter1(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast1(t_list *lst);
t_list		*ft_lstmap1(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew1(void *content);
int			ft_lstsize1(t_list *lst);
void		ft_free_strs(char *s1, char *s2, char *s3);
void		*free_arr(char ***arr);
char		*ft_skipnchar(const char *str, int n, char *skip);
char		*ft_strndup(const char *s1, size_t n);
char		**ft_arrdup(char **arr, int add);
void		err_msg(char *str, int option);
char		*get_str(char **envp, char *reference);
//void		*freedom(char ***arr);
void		output_prompts(void);
char		*ft_strcut(char *str, char *set);
//////////////////******* EXTRA FUNCTIONS FROM LIBFT /////////////////////

//////////////////******* PIPEX UTILS /////////////////////
int			set_name(t_command *cmd);
int			*redirect(char **red_arr, int fd_pair[2], t_command *cmd);
int			pipex(t_command *commands);
int			chk_builtin(t_command *commands);
int			check_fd_ret(int fd_redir[2], int fd[2], t_command *cmd);
int			last_fork(t_command *commands);
int			control(char *delim, t_command *cmd);
void		error_pipex(char *str);
void		ft_signal_cltr_c(int sig);
void		set_signals(void);
void		signal_in_child(void);
void		ft_signal_pipes(int sig);
void		signal_in_pipes(void);
int			command_len(t_command *command);
void		fill_fd(int *fd_arr, int count);
int			command_len(t_command *command);
//////////////////******* PIPEX UTILS /////////////////////

//////////////////******* NEW BUILTIN FUNCTIONS /////////////////////
int			ft_cd1(char **argv);
int			ft_echo1(char **argv);
int			ft_env1(char **argv);
int			exit_success(void);
int			exit_num(char *argv);
int			arg_error(void);
int			num_error(char *argv);
int			ft_exit(char **argv);
void		*export_error(char **new);
char		**change_env(char *new_str, char **envp, char *name);
char		**add_env(char *new_str, char **envp);
char		**do_export(char *argv);
int			ft_export(char **argv);
int			ft_pwd1(void);
int			ft_unset(char **argv);
int			is_correct(char *argv);
void		unset_error(char *argv, int *code);
char		**do_unset(char *argv);
int			ft_isnumeric(char *str);
uint64_t	ft_atoul(const char *str);
int			ft_arrlen(char **array);
//////////////////******* NEW BUILTIN FUNCTIONS /////////////////////

#endif