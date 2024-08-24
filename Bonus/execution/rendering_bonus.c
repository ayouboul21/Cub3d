/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:45:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/24 22:47:24 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	init_map(t_map *map)
{
	map->mlx.width = 1280;
	map->mlx.height = 720;
	map->mlx.mlx = mlx_init(map->mlx.width, map->mlx.height, "cub3d", false);
	map->mlx.img = mlx_new_image(map->mlx.mlx, map->mlx.width, map->mlx.height);
	map->txt[0] = mlx_load_png(map->west);
	map->txt[1] = mlx_load_png(map->north);
	map->txt[2] = mlx_load_png(map->south);
	map->txt[3] = mlx_load_png(map->east);
	map->txt[4] = mlx_load_png("./texture/dooro1.png");
	if (!map->txt[0] || !map->txt[1] || !map->txt[2]
		|| !map->txt[3] || !map->txt[4])
		ft_exit(*map, 1);
	hands_init(map);
	map->cell_height = 64;
	map->cell_width = 64;
	map->player.x = map->player.x * map->cell_width + map->cell_width / 2;
	map->player.y = map->player.y * map->cell_height + map->cell_height / 2;
	map->player.speed = map->cell_width / 20;
	map->fov = 60;
	map->ray_count = map->mlx.width;
	map->player.wall_height = 100;
	map->epsilon = map->cell_width / 10;
	map->map_width = map->mlx.width / 5;
	map->map_height = map->mlx.height / 5;
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
	draw_mini_map(map);
	draw_hands(map);
	mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}

void	render_map(t_map *map)
{
	init_map(map);
	render_frame(map);
	mlx_key_hook(map->mlx.mlx, ft_key_hook, map);
	mlx_loop_hook(map->mlx.mlx, ft_hook, map);
	mlx_loop(map->mlx.mlx);
	mlx_terminate(map->mlx.mlx);
}
