/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_wall_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 20:02:40 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/21 22:18:30 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	distance_to_wall(t_map *map, double x, double y)
{
	t_ray	ray;

	ray.x = x;
	ray.y = y;
	ray.angle = map->player.angle * M_PI / 180.0;
	get_ray_distance(map, &ray);
	if (ray.distance < map->epsilon)
		return (0);
	return (1);
}
