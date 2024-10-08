/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:43:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/09/04 10:47:21 by aoulahra         ###   ########.fr       */
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

typedef struct s_door
{
	int				x;
	int				y;
}				t_door;

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
	double		y_check_hor;
	double		x_check_ver;
	double		y_check_ver;
	double		distance;
	t_direction	rdir;
}				t_ray;

typedef struct s_map
{
	int				i;
	int				j;
	int				p;
	int				x;
	int				y;
	int				c;
	int				m;
	int				fm;
	int				clr;
	int				rows;
	int				cols;
	int				cell_height;
	int				cell_width;
	int				flag;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**map;
	char			*floor_color;
	char			*ceiling_color;
	t_mlx			mlx;
	t_ray			ray;
	double			h_x;
	double			h_y;
	double			fov;
	double			h_min;
	double			h_max;
	double			epsilon;
	double			ray_count;
	double			map_width;
	double			map_height;
	t_door			door;
	t_color			floor;
	t_color			ceiling;
	t_player		player;
	mlx_texture_t	*txt[5];
	mlx_texture_t	*txt2[8];
}				t_map;

int			parse(char *file, t_map *map);
int			spliter(char*str);
int			check_map(int fd, t_map *map);
int			check_door(t_map *map, int i, int j);
int			ft_tablen(char **tab);
int			check_line(char *line);
int			check_zero(t_map *map);
int			check_north(char *line, t_map *map);
int			check_south(char *line, t_map *map);
int			check_west(char *line, t_map *map);
int			check_east(char *line, t_map *map);
int			is_door_or_wall(t_map *map, int x, int y);
int			first_line_last(t_map *map);
int			check_ceiling_color(char *line, t_map *map);
int			check_floor_color(char *line, t_map *map);
int			mlx_get_pixel(mlx_texture_t *texture, int x, int y);
int			wall_hit_hor(t_map *map, double c_x, double c_y, t_ray *ray);
int			wall_hit_ver(t_map *map, double c_x, double c_y, t_ray *ray);
int			distance_to_wall(t_map *map, double x, double y, double angle);
char		**ft_split_whitespaces(char *str);
char		*skip_empty_lines(int fd, t_map *map);
void		set_near_door(t_map *map, int *door_x, int *door_y);
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
void		ft_hook(void *param);
void		ft_remap(t_map *map);
void		draw_image(t_map *map, double i, double j);
void		draw_wall(t_map *map, t_ray ray, double i);
void		ft_mouse_hook(t_map *map);
void		open_doors(t_map *map);
void		get_ray_distance(t_map *map, t_ray *ray);
void		ft_key_hook(struct mlx_key_data key, void *arg);
void		hands_init(t_map *map);
void		draw_hands(t_map *map);
void		cast_door_ray(t_map *map, t_ray *ray, t_door *door);
void		draw_mini_map(t_map *map);
uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//printer
void		printer(t_map *map);

#endif