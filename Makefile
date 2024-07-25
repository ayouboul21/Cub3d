SRC		=	 ft_malloc.c cub3d.c parsing/parse.c parsing/parse_utils.c parsing/check_directions.c

OBJ		= $(SRC:.c=.o)
HEADER	= cub3d.h
NAME	= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -O3
LIBFT	= libft/libft.a
GNL = get_next_line/get_next_line.c
GNL_UTILS = get_next_line/get_next_line_utils.c
GNL_HEADER = get_next_line/get_next_line.h

all: pre $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(HEADER) $(GNL) $(GNL_UTILS) $(GNL_HEADER)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(MLXFLAGS) $(LIBFT) $(GNL) $(GNL_UTILS)

%.o : %.c $(HEADER) $(GNL) $(GNL_UTILS) $(GNL_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I libft -I get_next_line

pre:
	@$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	@cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	@cd libft && make fclean

re: fclean all

.PHONY: clean
