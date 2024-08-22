/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:50:25 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/22 13:50:41 by aoulahra         ###   ########.fr       */
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

void	get_closest_door(t_map *map, int cell_x, int cell_y, t_door *door)
{
	int		i;
	int		j;
	double	distance;
	double	min_distance;

	i = cell_y - 2;
	min_distance = map->cell_width * 2;
	while (++i < cell_y + 1)
	{
		j = cell_x - 2;
		while (++j < map->cols + 1)
		{
			if ((map->map[i][j] == 'D' || map->map[i][j] == 'O')
				&& (i != cell_y || j != cell_x))
			{
				distance = sqrt(pow(cell_x - j, 2) + pow(cell_y - i, 2));
				if (distance < min_distance)
				{
					min_distance = distance;
					door->x = j;
					door->y = i;
				}
			}
		}
	}
}

void	open_doors(t_map *map)
{
	int		cell_x;
	int		cell_y;
	t_door	door;

	cell_y = (int)(map->player.y / map->cell_height);
	cell_x = (int)(map->player.x / map->cell_width);
	door = map->door;
	get_closest_door(map, cell_x, cell_y, &door);
	if (map->map[door.y][door.x] == 'D')
		map->map[door.y][door.x] = 'O';
	else if (map->map[door.y][door.x] == 'O')
		map->map[door.y][door.x] = 'D';
	render_frame(map);
}
