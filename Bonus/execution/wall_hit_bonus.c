/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hit_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 10:27:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/18 10:30:58 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	wall_hit_hor(t_map *map, double c_x, double c_y, t_ray *ray)
{
	int		x;
	int		y;

	x = floor(c_x / map->cell_width);
	y = floor(c_y / map->cell_height);
	if (x < 0 || x >= map->cols
		|| y < 0 || y >= map->rows)
		return (1);
	ray->wall_hor = (map->map[y][x] == 'D');
	if (map->map[y][x] == '1' || map->map[y][x] == 'D')
		return (1);
	if (cos(ray->angle) >= 0 && sin(ray->angle) <= 0)
		if ((map->map[y + 1][x] == '1' || map->map[y + 1][x] == 'D')
			&& (map->map[y][x - 1] == '1' || map->map[y][x - 1] == 'D'))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) <= 0)
		if ((map->map[y + 1][x] == '1' || map->map[y + 1][x] == 'D')
			&& (map->map[y][x + 1] == '1' || map->map[y][x + 1] == 'D'))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) >= 0)
		if ((map->map[y - 1][x] == '1' || map->map[y - 1][x] == 'D')
			&& (map->map[y][x + 1] == '1' || map->map[y][x + 1] == 'D'))
			return (1);
	return (0);
}

int	wall_hit_ver(t_map *map, double c_x, double c_y, t_ray *ray)
{
	int		x;
	int		y;

	x = floor(c_x / map->cell_width);
	y = floor(c_y / map->cell_height);
	if (x < 0 || x >= map->cols
		|| y < 0 || y >= map->rows)
		return (1);
	ray->wall_ver = (map->map[y][x] == 'D');
	if (map->map[y][x] == '1' || map->map[y][x] == 'D')
		return (1);
	if (cos(ray->angle) >= 0 && sin(ray->angle) <= 0)
		if ((map->map[y + 1][x] == '1' || map->map[y + 1][x] == 'D')
			&& (map->map[y][x - 1] == '1' || map->map[y][x - 1] == 'D'))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) <= 0)
		if ((map->map[y + 1][x] == '1' || map->map[y + 1][x] == 'D')
			&& (map->map[y][x + 1] == '1' || map->map[y][x + 1] == 'D'))
			return (1);
	if (cos(ray->angle) <= 0 && sin(ray->angle) >= 0)
		if ((map->map[y - 1][x] == '1' || map->map[y - 1][x] == 'D')
			&& (map->map[y][x + 1] == '1' || map->map[y][x + 1] == 'D'))
			return (1);
	return (0);
}
