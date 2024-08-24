/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:50:25 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/24 22:37:57 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_key_hook(struct mlx_key_data key, void *arg)
{
	t_map	*map;

	map = (t_map *)arg;
	if (key.key == MLX_KEY_SPACE && key.action == MLX_RELEASE)
		open_doors(map);
}

void	get_closest_door(t_map *map, t_door *door)
{
	t_ray	ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.x = map->player.x;
	ray.y = map->player.y;
	ray.angle = map->player.angle * (M_PI / 180);
	cast_door_ray(map, &ray, door);
}

void	open_doors(t_map *map)
{
	t_door	door;

	ft_bzero(&door, sizeof(t_door));
	get_closest_door(map, &door);
	if (door.x < 0 || door.x >= map->cols
		|| door.y < 0 || door.y >= map->rows)
		return ;
	if (map->map[door.y][door.x] == 'D')
		map->map[door.y][door.x] = 'O';
	else if (map->map[door.y][door.x] == 'O')
		map->map[door.y][door.x] = 'D';
	render_frame(map);
}
