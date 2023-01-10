# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hheggy <hheggy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 18:36:40 by kpanikka          #+#    #+#              #
#    Updated: 2023/01/10 19:55:26 by hheggy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
cc		= gcc -g
CFLAG	= -Wall -Werror -Wextra -I libft/ -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib
RMFLAG  = -f
SRC		= minishell.c \
		builtin_functions/builtin_utils.c \
		builtin_functions/cd.c \
		builtin_functions/echo.c \
		builtin_functions/env.c \
		builtin_functions/exit.c \
		builtin_functions/export.c \
		builtin_functions/pwd.c \
		builtin_functions/unset.c \
		ultimate_parser/command_line.c \
		ultimate_parser/command.c \
		ultimate_parser/expand.c \
		ultimate_parser/get.c \
		ultimate_parser/parser_utils.c \
		ultimate_parser/parser_utils2.c \
		ultimate_parser/parser.c \
		ultimate_parser/skip.c \
		pipex/here_doc.c \
		pipex/pipex_last.c \
		pipex/pipex_utils.c \
		pipex/pipex.c \
		pipex/redirects.c \
		pipex/signals.c \
		extrafunctions/ft_skipchar.c \
		extrafunctions/utils4.c \
		extrafunctions/utils3.c \
		extrafunctions/utils2.c \
		extrafunctions/utils.c
LIBFT	= -L libft -lft


OBJS	= $(SRC:.c=.o)

all		: $(NAME)

bonus	: all
 
%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean	:
		@make clean -C libft/
		$(RM) $(RMFLAG) $(OBJS)

fclean	: clean
	$(RM) $(RMFLAG) $(NAME)

re		: fclean all

$(NAME) : $(OBJS)
		@echo "\n"
		@echo "\033[0;32m*************************\n"
		@make -C libft/

		@echo "Compiling minishell...\n"
		@echo "*************************\n"

		@$(cc) $(CFLAG) $(OBJS) -o  $(NAME) $(LIBFT) -lreadline 
		@echo "\n\033[0mDone !"

.PHONY : all clean fclean re