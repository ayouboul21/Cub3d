 SRC     = cub3d.c parsing/parse.c parsing/parse_utils.c parsing/check_directions.c parsing/check_color.c parsing/check_map.c  parsing/check_map_utils.c \
 			execution/rendering.c execution/moves.c execution/ray_casting.c execution/hooks.c execution/draw_image.c .print.c

OBJ     = $(SRC:.c=.o)
HEADER  = cub3d.h
NAME    = cub3d
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O3 -ffast-math
RM      = rm -f
MLX     = .MLX42/build/libmlx42.a
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -Iinclude -IMLX42 -Ilibft
LIB     = -L"/Users/${USER}/.brew/Cellar/glfw/3.4/lib/"
LIBFT   = libft/libft.a

all: pre $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(LIB) $(MLXFLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

mlx :
	@cd .MLX42 && cmake -B build && cmake --build build -j4

pre: mlx
	@$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	@cd libft && make clean
	@cd .MLX42/build && make clean

fclean: clean
	$(RM) $(NAME) $(MLX)
	@cd libft && make fclean

re: fclean all

.PHONY: clean mlx
