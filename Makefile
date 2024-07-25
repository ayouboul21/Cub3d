SRC		=	cub3d.c

OBJ		= $(SRC:.c=.o)
HEADER	= cub3d.h
NAME	= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -O3
LIBFT	= libft/libft.a

all: pre $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(MLXFLAGS) $(LIBFT)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

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
