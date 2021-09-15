# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoat <bgoat@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 16:35:39 by bgoat             #+#    #+#              #
#    Updated: 2021/03/10 13:08:29 by bgoat            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a

SRCS=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
	ft_memchr.c ft_memcmp.c\
		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
	ft_strnstr.c ft_strncmp.c\
		ft_atoi.c\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_toupper.c ft_tolower.c\
		ft_calloc.c ft_strdup.c\
		\
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_putchar_fd.c\
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_split.c\
		
BONUS_SRCS= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_isspace_bonus.c

OBJS= $(SRCS:.c=.o)

BONUS_OBJS= $(BONUS_SRCS:.c=.o)

CC= gcc

INCLS= -I

FLAGS= -Wall -Werror -Wextra

HEADERS= libft.h

RM= rm -f

GREEN= \033[92m
ENDCOLOR= \x1B[0m

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLS)$(HEADERS) -c $<

$(NAME):	$(OBJS)
	ar rcs $(NAME) $^

bonus:	$(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $^
	echo "libft ${GREEN}is compiled${ENDCOLOR}"

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus

.SILENT:
