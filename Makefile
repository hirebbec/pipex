# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirebbec <hirebbec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 17:22:57 by hirebbec          #+#    #+#              #
#    Updated: 2022/03/02 17:51:02 by hirebbec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

NAME_BONUS = pipex_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

FILES = mandatory/main.c includes/ft_split.c includes/ft_strchr.c includes/ft_strdup.c includes/ft_strjoin.c includes/ft_strlen.c \
		includes/ft_strtrim.c includes/ft_substr.c mandatory/src.c  includes/ft_strncmp.c mandatory/utils.c mandatory/another_utils.c
FILES_BONUS =	bonus/main.c bonus/src.c includes/ft_split.c includes/ft_strchr.c includes/ft_strdup.c includes/ft_strjoin.c includes/ft_strlen.c \
		includes/ft_strtrim.c includes/ft_substr.c mandatory/src.c  includes/ft_strncmp.c bonus/forks.c mandatory/utils.c mandatory/another_utils.c \
		bonus/here_doc_case.c bonus/utils.c
 
OBJS = $(FILES:%.c=%.o)

OBJS_BONUS = $(FILES_BONUS:%.c=%.o)

%.o: %.c pipex.h
	$(CC) $(FLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

all: $(NAME)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY:all clean fclean re bonus
