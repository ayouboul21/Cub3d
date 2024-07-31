/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/31 14:35:53 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int is_inside_triangle(int i, int j, int *v)
{
    float	alpha;
	float	beta;
	float	denominator;

    denominator = (float)((v[3] - v[5]) * (v[0] - v[4]) + (v[4] - v[2]) * (v[1] - v[5]));
    alpha = ((float)((v[3] - v[5]) * (i - v[4]) + (v[4] - v[2]) * (j - v[5]))) / denominator;
    beta = ((float)((v[5] - v[1]) * (i - v[4]) + (v[0] - v[4]) * (j - v[5]))) / denominator;
    return (alpha >= 0 && beta >= 0 && 1 - alpha - beta >= 0);
}

void	color(mlx_image_t *img, uint32_t color, t_map *map)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset_x;
	uint32_t	offset_y;

	offset_x = (img->width / map->cols) * map->j;
	offset_y = (img->height / map->rows) * map->i;
	i = offset_x;
	while (i < offset_x + img->width / map->cols - 1)
	{
		j = offset_y;
		while (j < offset_y + img->height / map->rows - 1)
		{
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void calculate_vertices(t_map *map, float half_width, float half_height, int *v)
{
    float 		angle;
	t_player	player;

	player = map->player;
	angle = map->player.angle * M_PI / 180.0;
    v[0] = player.x + (player.x - player.x) * cos(angle)
		- (player.y - half_height - player.y) * sin(angle);
    v[1] = player.y + (player.x - player.x) * sin(angle)
		+ (player.y - half_height - player.y) * cos(angle);
    v[2] = player.x + (player.x - half_width - player.x)
		* cos(angle) - (player.y + half_height - player.y) * sin(angle);
    v[3] = player.y + (player.x - half_width - player.x)
		* sin(angle) + (player.y + half_height - player.y) * cos(angle);
    v[4] = player.x + (player.x + half_width - player.x)
		* cos(angle) - (player.y + half_height - player.y) * sin(angle);
    v[5] = player.y + (player.x + half_width - player.x)
		* sin(angle) + (player.y + half_height - player.y) * cos(angle);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->width = 1200;
	mlx->height = 600;
	mlx->mlx = mlx_init(mlx->width, mlx->height, "cub3d", false);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
}

void ft_hook(void* param)
{
    t_map *map;

    map = (t_map *)param;
    if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_ESCAPE))
        return (mlx_close_window(map->mlx.mlx));
    else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_LEFT))
    {
		mlx_delete_image(map->mlx.mlx, map->mlx.img);
		map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
        map->player.angle -= 5;
        if (map->player.angle < 0)
            map->player.angle += 360;
		render_frame(map);
    }
    else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_RIGHT))
    {
		mlx_delete_image(map->mlx.mlx, map->mlx.img);
		map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
        map->player.angle += 5;
        if (map->player.angle >= 360)
            map->player.angle -= 360;
		render_frame(map);
    }
    else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_S))
		move_backward(map);
    else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_W))
		move_forward(map);
    else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_A))
		move_left(map);
    else if (mlx_is_key_down(map->mlx.mlx, MLX_KEY_D))
		move_right(map);
}

void	init_map(t_map *map)
{
	map->player.x = map->player.x * map->mlx.width / map->cols + map->mlx.width / map->cols / 2;
	map->player.y = map->player.y * map->mlx.height / map->rows + map->mlx.height / map->rows / 2;
	map->cell_height = map->mlx.height / map->rows;
	map->cell_width = map->mlx.width / map->cols;
}

void	cast_ray(t_map *map)
{
	t_ray	ray;
	int		i;
	int		j;

	ray.angle = (map->player.angle - 90) * M_PI / 180.0;
	ray.x = map->player.x;
	ray.y = map->player.y;
	ray.distance = 0;
	while (ray.distance < 1000)
	{
		ray.x += cos(ray.angle);
		ray.y += sin(ray.angle);
		ray.distance += 1;
		i = ray.x;
		j = ray.y;
		if (i < 0 || i >= map->mlx.width || j < 0 || j >= map->mlx.height)
			break ;
		mlx_put_pixel(map->mlx.img, i, j, ft_pixel(255, 0, 0, 255));
		if (map->map[(int)(j / map->cell_height)][(int)(i / map->cell_width)] == '1')
			break ;
	}
	mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}

void	draw_player(t_map *map)
{
	int	v[6];
	int	i;
	int	j;

	calculate_vertices(map, map->cell_width / 4, map->cell_height / 4, v);
	i = map->player.x - map->cell_width / 4;
	while (++i < map->mlx.width)
	{
		j = map->player.y - map->cell_height / 4;
		while (++j < map->mlx.height)
			if (is_inside_triangle(i, j, v))
				mlx_put_pixel(map->mlx.img, i, j, ft_pixel(0, 255, 0, 255));
	}
	cast_ray(map);
}

void	render_frame(t_map *map)
{
	int32_t	i;
	int32_t	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			(1) && (map->i = i, map->j = j);
			if (map->map[i][j] == '1')
				color(map->mlx.img, ft_pixel(0, 0, 0, 255), map);
			else
			{
				(1) && (map->i = i, map->j = j);
				color(map->mlx.img, ft_pixel(255, 255, 255, 255), map);
			}
		}
	}
	draw_player(map);
}

void	render_map(t_map *map)
{
	init_mlx(&map->mlx);
	init_map(map);
	render_frame(map);
	mlx_loop_hook(map->mlx.mlx, ft_hook, map);
	mlx_loop(map->mlx.mlx);
	mlx_terminate(map->mlx.mlx);
}

