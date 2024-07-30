/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/30 10:44:46 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include ".MLX42/MLX42.h"

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}		t_color;

typedef struct s_player
{
	int	x;
	int	y;
	int	dir;
	int	angle;
}		t_player;


typedef struct s_mlx
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlx;

typedef struct s_ray
{
	double		angle;
	double		x;
	double		y;
	double		distance;
}				t_ray;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			i;
	int			j;
	int			p;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**map;
	char		*sprite;
	char		*floor_color;
	char		*ceiling_color;
	t_mlx		mlx;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
}				t_map;

int		parse(char *file, t_map *map);
int		ft_tablen(char **tab);
int		check_north(char *line, t_map *map);
int		check_south(char *line, t_map *map);
int		check_west(char *line, t_map *map);
int		check_east(char *line, t_map *map);
int		check_ceiling_color(char *line, t_map *map);
int		check_floor_color(char *line, t_map *map);
char	**ft_split_whitespaces(char *str);
char	*skip_empty_lines(int fd, t_map *map);
int		check_map(int fd, t_map *map);
int		check_line(char *line);
void	add_last(char ***map, char *data);
void	free_tab(char ***args);
void	ft_exit(t_map map, int status);
int		first_line_last(t_map *map);
int		spliter(char*str);
int		chek_zero(t_map *map);
void	render_map(t_map *map);

//printer
void	printer(t_map *map);

#endif