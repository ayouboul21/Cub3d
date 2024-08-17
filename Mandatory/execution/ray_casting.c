/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:32:53 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/15 17:09:24 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_hit(t_map *map, double x, double y, t_ray *ray)
{
	int		cell_x;
	int		cell_y;

	cell_x = floor(x / map->cell_width);
	cell_y = floor(y / map->cell_height);
	if (cell_x < 0 || cell_x >= map->cols
		|| cell_y < 0 || cell_y >= map->rows)
		return (1);
	if (map->map[cell_y][cell_x] == '1')
		return (1);
	if (cos(ray->angle) >= 0 && sin(ray->angle) <= 0)
		if (map->map[cell_y + 1][cell_x] == '1'
			&& map->map[cell_y][cell_x - 1] == '1')
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) <= 0)
		if (map->map[cell_y + 1][cell_x] == '1'
			&& map->map[cell_y][cell_x + 1] == '1')
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) >= 0)
		if (map->map[cell_y - 1][cell_x] == '1'
			&& map->map[cell_y][cell_x + 1] == '1')
			return (1);
	return (0);
}

double	get_ver_distance(t_map *map, t_ray *ray, int looksdown, int looksright)
{
	double	x;
	double	y;

	if (looksright)
		x = floor((ray->x / map->cell_width))
			* map->cell_width + map->cell_width;
	else
		x = floor((ray->x / map->cell_width)) * map->cell_width - 0.001;
	y = (x - ray->x) * tan(ray->angle) + ray->y;
	ray->x_step = map->cell_width;
	ray->y_step = map->cell_width * tan(ray->angle);
	(!looksright) && (ray->x_step *= -1);
	(!looksdown && ray->y_step > 0) && (ray->y_step *= -1);
	(looksdown && ray->y_step < 0) && (ray->y_step *= -1);
	while (!wall_hit(map, x, y, ray))
	{
		x += ray->x_step;
		y += ray->y_step;
	}
	ray->x_check_ver = x;
	ray->y_check = y;
	return (sqrt(pow(ray->x - ray->x_check_ver, 2) + pow(ray->y
				- ray->y_check, 2)) * cos(ray->angle
			- (map->player.angle * M_PI / 180.0)));
}

double	get_hor_distance(t_map *map, t_ray *ray, int looksdown, int looksright)
{
	double	x;
	double	y;

	if (looksdown)
		y = floor((ray->y / map->cell_height))
			* map->cell_height + map->cell_height;
	else
		y = floor((ray->y / map->cell_height)) * map->cell_height - 0.001;
	x = (y - ray->y) / tan(ray->angle) + ray->x;
	ray->y_step = map->cell_height;
	ray->x_step = map->cell_height / tan(ray->angle);
	(!looksdown) && (ray->y_step *= -1);
	(!looksright && ray->x_step > 0) && (ray->x_step *= -1);
	(looksright && ray->x_step < 0) && (ray->x_step *= -1);
	while (!wall_hit(map, x, y, ray))
	{
		y += ray->y_step;
		x += ray->x_step;
	}
	ray->x_check_hor = x;
	ray->y_check = y;
	return (sqrt(pow(ray->x - ray->x_check_hor, 2)
			+ pow(ray->y - ray->y_check, 2))
		* cos(ray->angle - (map->player.angle * M_PI / 180.0)));
}

void	get_ray_distance(t_map *map, t_ray *ray)
{
	double	hor_distance;
	double	ver_distance;

	hor_distance = get_hor_distance(map, ray,
			sin(ray->angle) > 0, cos(ray->angle) > 0);
	ver_distance = get_ver_distance(map, ray,
			sin(ray->angle) > 0, cos(ray->angle) > 0);
	if (hor_distance < ver_distance)
	{
		ray->x_check = ray->x_check_hor;
		ray->rdir = HORIZONTAL;
	}
	else
	{
		ray->x_check = ray->y_check;
		ray->rdir = VERTICAL;
	}
	ray->distance = fmin(hor_distance, ver_distance);
}

void	cast_rays(t_map *map)
{
	double		i;
	t_ray		ray;

	i = 0;
	map->player.ray_angle = map->player.angle - map->fov / 2;
	while ((int)i < map->mlx.width)
	{
		ft_bzero(&ray, sizeof(t_ray));
		ray.angle = map->player.ray_angle * M_PI / 180.0;
		ray.x = map->player.x;
		ray.y = map->player.y;
		get_ray_distance(map, &ray);
		draw_wall(map, ray, i);
		map->player.ray_angle += map->fov / map->ray_count;
		if (map->player.ray_angle < 0)
			map->player.ray_angle += 360;
		if (map->player.ray_angle > 360)
			map->player.ray_angle -= 360;
		i++;
	}
	mlx_image_to_window(map->mlx.mlx, map->mlx.img, 0, 0);
}
