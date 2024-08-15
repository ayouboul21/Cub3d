/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/15 11:32:22 by aoulahra         ###   ########.fr       */
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
	int		dir;
	double	angle;
	double	ray_angle;
	double	x;
	double	y;
	double	speed;
	double	wall_height;
}		t_player;

typedef struct s_mlx
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlx;

typedef	enum  e_direction
{
	HORIZONTAL,
	VERTICAL
}				t_direction;

typedef struct s_ray
{
	double		angle;
	double		x;
	double		y;
	double		x_step;
	double		y_step;
	double		x_check;
	double		y_check;
	double		x_check_hor;
	double		x_check_ver;
	double		distance;
	t_direction	rdir;
}				t_ray;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			i;
	int			j;
	int			p;
	int			cell_height;
	int			cell_width;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**map;
	char		*sprite;
	char		*floor_color;
	char		*ceiling_color;
	double		fov;
	double		ray_count;
	t_mlx		mlx;
	t_ray		ray;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	mlx_texture_t	*texture;
}				t_map;

int			parse(char *file, t_map *map);
int			ft_tablen(char **tab);
int			check_north(char *line, t_map *map);
int			check_south(char *line, t_map *map);
int			check_west(char *line, t_map *map);
int			check_east(char *line, t_map *map);
int			check_ceiling_color(char *line, t_map *map);
int			check_floor_color(char *line, t_map *map);
char		**ft_split_whitespaces(char *str);
char		*skip_empty_lines(int fd, t_map *map);
int			check_map(int fd, t_map *map);
int			check_line(char *line);
void		add_last(char ***map, char *data);
void		free_tab(char ***args);
void		ft_exit(t_map map, int status);
int			first_line_last(t_map *map);
int			spliter(char*str);
int			chek_zero(t_map *map);
void		render_map(t_map *map);
void		render_frame(t_map *map);
void		move_forward(t_map *map);
void		move_backward(t_map *map);
void		move_left(t_map *map);
void		move_right(t_map *map);
void		rotate_left(t_map *map);
void		rotate_right(t_map *map);
void		cast_rays(t_map *map);
void		cast_ray(t_map *map, double i);
void		ft_hook(void *param);
void		ft_remap(t_map *map);
void		draw_player(t_map *map);
void		color(mlx_image_t *img, uint32_t color, t_map *map);
void		draw_image(t_map *map, double i, double j, double h_min, double h_max);
uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//printer
void	printer(t_map *map);

#endif