# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelsiddi <aelsiddi@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 18:36:40 by kpanikka          #+#    #+#              #
#    Updated: 2023/01/15 18:13:12 by aelsiddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
cc		= gcc -g
CFLAG	= -Wall -Werror -Wextra -I libft/ -I/usr/local/opt/readline/include 
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
	@$(CC) $(CFLAG) -c $< -o $@

clean	:
		@make clean -C libft/
		@$(RM) $(RMFLAG) $(OBJS)

fclean	: clean
	$(RM) $(RMFLAG) $(NAME)

re		: fclean all

$(NAME) : $(OBJS)
		@echo "\n"
		@echo "\033[0;32m*************************\n"
		@make -C libft/

		@echo "Compiling minishell...\n"
		@echo "*************************\n"
		@echo "                                                                                                           ,oo.                                                                        "
		@echo "                                                   .....                                              ....'dWNo.....                                                                  "    
		@echo "                                                  'kXXX0;                                         'cdk0KXXXWMWNXXXK0ko,.                'okkOd.                                       "    
		@echo "                                                  'kXXX0;                                       .oXMMMMMWNNWMMNNWWMMMMNx.               ;XMMMK,                                       "    
		@echo "                                                   .....                                       .dWMMWOl:,',xWNo',;lOWMMWd.              ;XMMMK,                                       "    
		@echo "                                                                                               ,KMMM0,     lNX:    ,0MMM0'              ;XMMMK,                                       "    
		@echo "               ......          ......                                      ......              :XMMMO.     lNX:    .oOkdc.              ;XMMMK,    ......                             "    
		@echo "    .oxxxc..:dk0KKKK0ko,   'lxOKKKKKKOxl'         .lxxxo'       :xxxd,.,lxO0KKKKKOxl'          cNMMMO.     lNX:                         ;XMMMKc,oxOKKKKKK0kdc.                        "    
		@echo "    ,KMMMKxOXK0000KNWMMNxcxXNXK0000XWMMWXo.       '0MMMX:      .xWMMWOkXNX000000NMMMXl'.       :XMMM0,     lNX:                         ;XMMMWXNNK00000KXWMMWXo.                      "    
		@echo "    ,KMMMW0c'.    .'dNMMWWNx;..   ..:OWMMXc       '0MMMX:      .xWMMMNk:'..    .;OWMMX0c       'OMMMWOl:;''dWX:                         ;XMMMW0c'.     ..c0MMMNc                      "    
		@echo "    ,KMMMNl         .kMMMWk.         cNMMWx.      '0MMMX:      .xWMMWk.          cNMMMWk.       :KMMMMMMWNXNMW0doc:,..                  ;XMMMWo           lNMMWx.                     "    
		@echo "    ,KMMMN:         .dWMMWd.         cNMMMO.      '0MMMX:      .xWMMWo           :XMMMM0'        'oOKNWWMMMMMMMMMMWWX0d;.               ;XMMMNc           lNMMMk.                     "    
		@echo "    ,KMMMX:         .dWMMWd.         cNMMMO.      '0MMMX:      .xWMMWo           :XMMMMK,           ..,;:ld0WWXKXNWMMMMNx.              ;XMMMX:           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd           :XMMMMK,                  lNXl..';oXMMMNo              ;XMMMX;           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,                  lNX:    .dWMMMO.             ;XMMMK,           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,                  lNX:     lNMMM0,             ;XMMMK,           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,      'clol'      lNX:     lNMMM0,             ;XMMMK,           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,     .kMMMNc      lNX:     cNMMMO.             ;XMMMK,           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,     .dWMMWk.     lNX:    .oWMMWd.             ;XMMMK,           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,      ;KMMMWOlc:,;xWNd;;:cxXMMMK;              ;XMMMK,           oWMMMO.                     "    
		@echo "    ,KMMMX:         .dWMMWx.         cNMMMO.      '0MMMX:      .xWMMWd.          :XMMMMK,       :0WMMMMMWWWWMMWWWWMMMMNO;               :XMMMK,           oWMMMO.                     "    
		@echo "    .oxxxo'          ;xxxx:          'dxxxc.      .lxxxo'       :xxxx;           'oxxxxo.        .;lxk0KKKKNMWNKKK0Oxl;.                'oxxxo.           ;dxxxc.                     "    
		@echo "                                                                                                      .....dWNl....                                                                   "     
		@echo "                                                                                                           cK0;                                                                       "    
		@echo "                                                                                                            ..                      .lxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;                  "
		@echo "                                                                                                                                    'kXXXXXXXXXXXXXXXXXXXXXXXXXXXXXl                  " 
		@$(cc) $(CFLAG) $(OBJS) -L/usr/local/opt/readline/lib -o  $(NAME) $(LIBFT) -lreadline 
		@echo "\n\033[0mDone !"

.PHONY : all clean fclean re