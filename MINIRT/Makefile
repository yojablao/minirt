NAME	=	MRT
HEAD	= 	../tool.h

PARS_PATH = parsing/
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Imlx 
AR		=	ar rc
RM		=	rm -f
SRCS	=	 $(PARS_PATH)get_next_line.c  $(PARS_PATH)get_next_line_utils.c  $(PARS_PATH)check_fn.c  main.c    $(PARS_PATH)parsing.c   $(PARS_PATH)type_object.c  $(PARS_PATH)utils.c\
			 $(PARS_PATH)ft_isdigit.c  $(PARS_PATH)ft_rang.c $(PARS_PATH)tools.c  $(PARS_PATH)ft_strncmp.c  $(PARS_PATH)ft_split.c  $(PARS_PATH)ft_atoi.c

OBJS	=	$(SRCS:%c=%o)


all	:	$(NAME)

$(NAME)	:	$(OBJS) 
			$(CC) $(OBJS)  -lmlx -framework OpenGL -framework AppKit  -o $(NAME)	-g -fsanitize=address

%o	:	%c $(HEAD) 
			$(CC) $(CFLAGS)  -c -o $@ $<

clean:
			$(RM) $(OBJS) $(B_OBJS)

fclean:	clean
			$(RM) $(NAME)

re:	fclean all