# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 16:44:25 by bluzi             #+#    #+#              #
#    Updated: 2023/05/05 20:36:16 by bluzi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex

CFLAGS		:= -Wextra -Wall -Werror
LIBFT		:= lib/libft

HEADERS		:= 	-I include
LIBS		:= 	$(LIBFT)/libft.a
SRCS		:= 	src/child.c      		\
				src/here_doc.c   		\
				src/main.c       		\
				src/parser.c     		\
				src/pipex.c      		\
				src/pipex_split.c		\
				src/utils.c
			
BNS_SRCS	:= 	bns_src/child_bonus.c      	\
				bns_src/here_doc_bonus.c   	\
				bns_src/main_bonus.c       	\
				bns_src/parser_bonus.c     	\
				bns_src/pipex_bonus.c      	\
				bns_src/pipex_split_bonus.c	\
				bns_src/utils_bonus.c
			
OBJS		:= ${SRCS:.c=.o}
BNS_OBJS	:= ${BNS_SRCS:.c=.o}

all: libft $(NAME)

libft:
	@make all -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS) $(BNS_OBJS)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

bonus: libft $(BNS_OBJS)
	@$(CC) $(BNS_OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	
re: fclean all

.PHONY: all, clean, fclean, re, libft, bonus