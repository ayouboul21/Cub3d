/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:27:48 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/25 10:53:00 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	door_hit_ver(t_map *map, double c_x, double c_y, t_ray *ray)
{
	int		x;
	int		y;

	x = floor(c_x / map->cell_width);
	y = floor(c_y / map->cell_height);
	if (x < 0 || x >= map->cols
		|| y < 0 || y >= map->rows)
		return (1);
	if (is_door_or_wall(map, x, y))
		return (1);
	if (cos(ray->angle) >= 0 && sin(ray->angle) <= 0)
		if (is_door_or_wall(map, x, y + 1) && is_door_or_wall(map, x - 1, y))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) <= 0)
		if (is_door_or_wall(map, x, y + 1) && is_door_or_wall(map, x + 1, y))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) >= 0)
		if (is_door_or_wall(map, x, y - 1) && is_door_or_wall(map, x + 1, y))
			return (1);
	return (0);
}

int	door_hit_hor(t_map *map, double c_x, double c_y, t_ray *ray)
{
	int		x;
	int		y;

	x = floor(c_x / map->cell_width);
	y = floor(c_y / map->cell_height);
	if (x < 0 || x >= map->cols
		|| y < 0 || y >= map->rows)
		return (1);
	if (is_door_or_wall(map, x, y))
		return (1);
	if (cos(ray->angle) >= 0 && sin(ray->angle) <= 0)
		if (is_door_or_wall(map, x, y + 1) && is_door_or_wall(map, x - 1, y))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) <= 0)
		if (is_door_or_wall(map, x, y + 1) && is_door_or_wall(map, x + 1, y))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) >= 0)
		if (is_door_or_wall(map, x, y - 1) && is_door_or_wall(map, x + 1, y))
			return (1);
	return (0);
}

double	door_ver_distance(t_map *map, t_ray *ray, int looksdown, int looksright)
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
	while (!door_hit_ver(map, x, y, ray))
	{
		x += ray->x_step;
		y += ray->y_step;
	}
	ray->x_check_ver = x;
	ray->y_check_ver = y;
	return (sqrt(pow(ray->x - ray->x_check_ver, 2) + pow(ray->y
				- ray->y_check, 2)));
}

double	door_hor_distance(t_map *map, t_ray *ray, int looksdown, int looksright)
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
	while (!door_hit_hor(map, x, y, ray))
	{
		y += ray->y_step;
		x += ray->x_step;
	}
	ray->x_check_hor = x;
	ray->y_check_hor = y;
	return (sqrt(pow(ray->x - ray->x_check_hor, 2)
			+ pow(ray->y - ray->y_check, 2)));
}

void	cast_door_ray(t_map *map, t_ray *ray, t_door *door)
{
	double	hor_distance;
	double	ver_distance;

	hor_distance = door_hor_distance(map, ray,
			sin(ray->angle) > 0, cos(ray->angle) > 0);
	ver_distance = door_ver_distance(map, ray,
			sin(ray->angle) > 0, cos(ray->angle) > 0);
	if (hor_distance < ver_distance)
	{
		door->x = floor(ray->x_check_hor / map->cell_width);
		door->y = floor(ray->y_check_hor / map->cell_height);
	}
	else
	{
		door->x = floor(ray->x_check_ver / map->cell_width);
		door->y = floor(ray->y_check_ver / map->cell_height);
	}
}
