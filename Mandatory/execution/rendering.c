/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/25 11:43:01 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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

void	init_map(t_map *map)
{
	map->mlx.width = 1280;
	map->mlx.height = 720;
	map->mlx.mlx = mlx_init(map->mlx.width, map->mlx.height, "cub3d", false);
	if (!map->mlx.mlx)
		ft_exit(*map, 1);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	if (!map->mlx.img)
		ft_exit(*map, 1);
	map->txt[0] = mlx_load_png(map->west);
	map->txt[1] = mlx_load_png(map->north);
	map->txt[2] = mlx_load_png(map->south);
	map->txt[3] = mlx_load_png(map->east);
	if (!map->txt[0] || !map->txt[1] || !map->txt[2] || !map->txt[3])
		ft_exit(*map, 1);
	map->cell_height = 128;
	map->cell_width = 128;
	map->player.x = map->player.x * map->cell_width + map->cell_width / 2;
	map->player.y = map->player.y * map->cell_height + map->cell_height / 2;
	map->player.speed = map->cell_width / 20;
	map->fov = 60;
	map->ray_count = map->mlx.width;
	map->player.wall_height = 200;
}

void	render_frame(t_map *map)
{
	double		i;
	t_ray		ray;

	i = 0;
	map->player.ray_angle = map->player.angle - map->fov / 2;
	while ((int)i < map->mlx.width)
	{
		ft_bzero(&ray, sizeof(t_ray));
		if (map->player.ray_angle < 0)
			map->player.ray_angle += 360;
		if (map->player.ray_angle > 360)
			map->player.ray_angle -= 360;
		ray.angle = map->player.ray_angle * M_PI / 180.0;
		ray.x = map->player.x;
		ray.y = map->player.y;
		get_ray_distance(map, &ray);
		draw_wall(map, ray, i);
		map->player.ray_angle += map->fov / map->ray_count;
		i++;
	}
	mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}

void	render_map(t_map *map)
{
	init_map(map);
	render_frame(map);
	mlx_loop_hook(map->mlx.mlx, ft_hook, map);
	mlx_loop(map->mlx.mlx);
}
