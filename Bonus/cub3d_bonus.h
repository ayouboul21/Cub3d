/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/18 10:34:28 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../.MLX42/include/MLX42/MLX42.h"

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

typedef enum e_direction
{
	HORIZONTAL,
	VERTICAL
}				t_direction;

typedef struct s_ray
{
	int			wall;
	int			wall_ver;
	int			wall_hor;
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
	int				rows;
	int				cols;
	int				i;
	int				j;
	int				p;
	int				cell_height;
	int				cell_width;
	int				clr;
	double			h_max;
	double			h_min;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**map;
	char			*sprite;
	char			*floor_color;
	char			*ceiling_color;
	double			fov;
	double			ray_count;
	t_mlx			mlx;
	t_ray			ray;
	t_color			floor;
	t_color			ceiling;
	t_player		player;
	mlx_texture_t	*txt[5];
}				t_map;

int			parse(char *file, t_map *map);
int			spliter(char*str);
int			check_map(int fd, t_map *map);
int			ft_tablen(char **tab);
int			check_line(char *line);
int			check_zero(t_map *map);
int			check_north(char *line, t_map *map);
int			check_south(char *line, t_map *map);
int			check_west(char *line, t_map *map);
int			check_east(char *line, t_map *map);
int			first_line_last(t_map *map);
int			check_ceiling_color(char *line, t_map *map);
int			check_floor_color(char *line, t_map *map);
int			wall_hit_hor(t_map *map, double c_x, double c_y, t_ray *ray);
int			wall_hit_ver(t_map *map, double c_x, double c_y, t_ray *ray);
char		**ft_split_whitespaces(char *str);
char		*skip_empty_lines(int fd, t_map *map);
void		add_last(char ***map, char *data);
void		free_tab(char ***args);
void		ft_exit(t_map map, int status);
void		render_map(t_map *map);
void		render_frame(t_map *map);
void		move_forward(t_map *map);
void		move_backward(t_map *map);
void		move_left(t_map *map);
void		move_right(t_map *map);
void		rotate_left(t_map *map);
void		rotate_right(t_map *map);
void		cast_rays(t_map *map);
void		ft_hook(void *param);
void		ft_remap(t_map *map);
void		color(mlx_image_t *img, uint32_t color, t_map *map);
void		draw_image(t_map *map, double i, double j);
void		draw_wall(t_map *map, t_ray ray, double i);
uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//printer
void		printer(t_map *map);

#endif