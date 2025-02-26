# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:40:42 by mthamir           #+#    #+#              #
#    Updated: 2025/02/23 14:28:25 by yojablao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minirt

NAME_BONUS := minirt_bonus

CC := cc -Ofast

FLAGS :=  -Ofast -I/Users/$(shell whoami)/Desktop/gitminirt/MLX42/include/MLX42

MLX		=	MLX42/libmlx42.a

SRC :=  _Mandatory/parse/utils_0.c _Mandatory/parse/utils_1.c _Mandatory/parse/char_to.c  \
		_Mandatory/parse/check_identfier.c _Mandatory/parse/error.c _Mandatory/parse/get_next_line.c \
		_Mandatory/parse/init_camera.c _Mandatory/parse/init_lighting.c _Mandatory/parse/init_objects.c \
		_Mandatory/parse/read_file.c _Mandatory/parse/split.c  \
		_Mandatory/prog_files/basic_operations.c _Mandatory/prog_files/camera.c \
		_Mandatory/prog_files/colors_operations.c _Mandatory/prog_files/cylinder.c   _Mandatory/prog_files/cylinder_intersection.c \
		_Mandatory/prog_files/inverse_0.c  _Mandatory/prog_files/inverse_1.c _Mandatory/prog_files/inverse_2.c \
		_Mandatory/prog_files/lighting.c _Mandatory/prog_files/matrix_operations_0.c  \
		_Mandatory/prog_files/matrix_operations_1.c _Mandatory/prog_files/plane.c _Mandatory/prog_files/plane_intersection.c \
		_Mandatory/prog_files/prepare_computing.c _Mandatory/prog_files/rays_operations.c \
		_Mandatory/prog_files/render.c _Mandatory/prog_files/sphere.c _Mandatory/prog_files/sphere_intersection.c \
		_Mandatory/prog_files/vectors_operations_0.c _Mandatory/prog_files/vectors_operations_1.c \
		_Mandatory/prog_files/vectors_operations_2.c _Mandatory/prog_files/world_intersection.c \


SRC_BONUS :=  _Bonus/parse_bonus/utils_0_bonus.c _Bonus/parse_bonus/utils_1_bonus.c _Bonus/parse_bonus/char_to_bonus.c  \
		_Bonus/parse_bonus/check_identfier_bonus.c _Bonus/parse_bonus/error_bonus.c _Bonus/parse_bonus/get_next_line_bonus.c \
		_Bonus/parse_bonus/init_camera_bonus.c _Bonus/parse_bonus/init_lighting_bonus.c _Bonus/parse_bonus/init_objects_bonus.c \
		_Bonus/parse_bonus/read_file_bonus.c _Bonus/parse_bonus/split_bonus.c  \
		_Bonus/prog_files_bonus/basic_operations_bonus.c _Bonus/prog_files_bonus/camera_bonus.c \
		_Bonus/prog_files_bonus/colors_operations_bonus.c _Bonus/prog_files_bonus/cylinder_bonus.c   _Bonus/prog_files_bonus/cylinder_intersection_bonus.c \
		_Bonus/prog_files_bonus/inverse_0_bonus.c  _Bonus/prog_files_bonus/inverse_1_bonus.c _Bonus/prog_files_bonus/inverse_2_bonus.c \
		_Bonus/prog_files_bonus/lighting_bonus.c _Bonus/prog_files_bonus/matrix_operations_0_bonus.c  \
		_Bonus/prog_files_bonus/matrix_operations_1_bonus.c _Bonus/prog_files_bonus/plane_bonus.c _Bonus/prog_files_bonus/plane_intersection_bonus.c \
		_Bonus/prog_files_bonus/prepare_computing_bonus.c _Bonus/prog_files_bonus/rays_operations_bonus.c \
		_Bonus/prog_files_bonus/render_bonus.c _Bonus/prog_files_bonus/sphere_bonus.c _Bonus/prog_files_bonus/sphere_intersection_bonus.c \
		_Bonus/prog_files_bonus/vectors_operations_0_bonus.c _Bonus/prog_files_bonus/vectors_operations_1_bonus.c \
		_Bonus/prog_files_bonus/vectors_operations_2_bonus.c _Bonus/prog_files_bonus/world_intersection_bonus.c _Bonus/prog_files_bonus/texter_bonus.c \

OBJ := $(SRC:.c=.o)

OBJ_BONUS := $(SRC_BONUS:bonus.c=bonus.o)

MLXF	=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L/Users/$(shell whoami)/.brew/opt/glfw/lib 

HEADER := minirt.h

HEADER_BONUS := minirt_bonus.h

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJ)
	cmake CMakeLists.txt -S MLX42/ -B MLX42/ 
	make -C MlX42
	$(CC) $(FLAGS) $(MLXF) $(OBJ) $(MLX) -o $(NAME)

$(NAME_BONUS) : $(OBJ_BONUS)
	cmake CMakeLists.txt -S MLX42/ -B MLX42/ 
	make -C MlX42
	$(CC) $(FLAGS) $(MLXF) $(OBJ_BONUS) $(MLX) -o $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

%bonus.o : %bonus.c $(HEADER_BONUS)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	make clean -C MLX42/
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

re_bonus : fclean bonus