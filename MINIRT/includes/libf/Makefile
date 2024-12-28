# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojablao <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 15:49:31 by yojablao          #+#    #+#              #
#    Updated: 2023/12/11 11:09:17 by yojablao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
HEAD	= 	libft.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g
AR		=	ar rc
RM		=	rm -f
SRCS	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
			ft_strlcpy.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_strlcat.c \
			ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 
			
BONUS	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \

OBJS	=	$(SRCS:%c=%o)

B_OBJS	=	$(BONUS:%c=%o)

%o	:	%c $(HEAD)
			$(CC) $(CFLAGS) -c -o $@ $<

$(NAME)	:	$(OBJS)
			ar rc $(NAME) $(OBJS)
			
all	:	$(NAME)

bonus:	$(B_OBJS)
			ar rc $(NAME) $(B_OBJS)

clean:
			$(RM) $(OBJS) $(B_OBJS)

fclean:	clean
			$(RM) $(NAME)

re:	fclean all