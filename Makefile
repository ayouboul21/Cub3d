 SRC     = Mandatory/cub3d.c Mandatory/parsing/parse.c Mandatory/parsing/parse_utils.c \
 			Mandatory/parsing/check_directions.c Mandatory/parsing/check_color.c \
			Mandatory/parsing/check_map.c  Mandatory/parsing/check_map_utils.c \
 			Mandatory/execution/rendering.c Mandatory/execution/moves.c Mandatory/execution/ray_casting.c \
			Mandatory/execution/hooks.c Mandatory/execution/draw_image.c Mandatory/.print.c

SRC_BONUS = Bonus/cub3d_bonus.c Bonus/parsing/parse_bonus.c Bonus/parsing/parse_utils_bonus.c \
 			Bonus/parsing/check_directions_bonus.c Bonus/parsing/check_color_bonus.c \
			Bonus/parsing/check_map_bonus.c  Bonus/parsing/check_map_utils_bonus.c \
 			Bonus/execution/rendering_bonus.c Bonus/execution/moves_bonus.c \
			Bonus/execution/ray_casting_bonus.c Bonus/execution/wall_hit_bonus.c \
			Bonus/execution/hooks_bonus.c Bonus/execution/draw_image_bonus.c \
			Bonus/.print_bonus.c Bonus/execution/door_bonus.c

OBJ     = $(SRC:.c=.o)
OBJ_BONUS     = $(SRC_BONUS:.c=.o)
HEADER  = Mandatory/cub3d.h
HEADER_BONUS  = Bonus/cub3d_bonus.h
NAME    = cub3d
NAME_BONUS    = cub3d_bonus
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

bonus : pre $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX) $(LIB) $(MLXFLAGS) -o $(NAME_BONUS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

mlx :
	@cd .MLX42 && cmake -B build && cmake --build build -j4

pre: mlx
	@$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)
	@cd libft && make clean
	@cd .MLX42/build && make clean

fclean: clean
	$(RM) $(NAME) $(MLX)
	$(RM) $(NAME_BONUS) $(MLX)
	@cd libft && make fclean

re: fclean all

bre: fclean bonus

.PHONY: clean mlx
