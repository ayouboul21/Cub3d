/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:32:53 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/01 10:41:33 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_rays(t_map *map)
{
	double	i;

	i = 0;
	map->player.ray_angle = map->player.angle + map->fov / 2;
	while (i < 60)
	{
		map->player.ray_angle = map->player.ray_angle
			- map->fov / map->ray_count;
		cast_ray(map);
		i += map->fov / map->ray_count;
	}
}

void	cast_ray(t_map *map)
{
	t_ray	ray;
	int		i;
	int		j;

	ray.angle = (map->player.ray_angle - 90) * M_PI / 180.0;
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
		if (map->map[(int)(j
				/ map->cell_height)][(int)(i / map->cell_width)] == '1')
			break ;
	}
	mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}
