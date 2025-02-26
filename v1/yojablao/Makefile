NAME	=	MRT
HEAD	= 	pars.h

PARS_PATH = parsing/
CC		=	cc #-g -fsanitize=address
# LDFLAGS = -Lminilibx_linux -lmlx -lX11 -lXext -lm
CFLAGS	=	 #-g  # -Iminilibx_linux   #-Wall -Wextra -Werror-g -fsanitize=address
AR		=	ar rc
RM		=	rm -f
SRCS	=	 $(PARS_PATH)get_next_line.c  $(PARS_PATH)get_next_line_utils.c $(PARS_PATH)print.c $(PARS_PATH)check_fn.c $(PARS_PATH)maloc_u.c main.c   $(PARS_PATH)parsing.c   $(PARS_PATH)type_object.c  $(PARS_PATH)utils.c\
			 $(PARS_PATH)ft_isdigit.c $(PARS_PATH)sp_lit.c $(PARS_PATH)ft_rang.c $(PARS_PATH)tools.c  $(PARS_PATH)ft_strncmp.c  $(PARS_PATH)ft_split.c  $(PARS_PATH)ft_atoi.c

OBJS	=	$(SRCS:%c=%o)


all	:	$(NAME)

$(NAME)	:	$(OBJS) 
			$(CC) $(OBJS)   -o $(NAME)	

%o	:	%c $(HEAD) 
			$(CC) $(CFLAGS)  -c -o $@ $< 

clean:
			$(RM) $(OBJS) 

fclean:	clean
			$(RM) $(NAME)

re:	fclean all