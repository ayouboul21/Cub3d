/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:50:25 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/20 18:04:46 by aoulahra         ###   ########.fr       */
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

void	ft_add_door_back(t_map *map, int i, int j)
{
	t_door	*new_door;
	t_door	*tmp;

	new_door = (t_door *)ft_malloc(sizeof(t_door));
	ft_bzero(new_door, sizeof(t_door));
	new_door->x = j;
	new_door->y = i;
	if (!map->door)
		map->door = new_door;
	else
	{
		tmp = map->door;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_door;
	}
}

void	open_doors(t_map *map)
{
	int		cell_x;
	int		cell_y;
	t_door	*tmp;

	cell_y = (int)(map->player.y / map->cell_height);
	cell_x = (int)(map->player.x / map->cell_width);
	tmp = map->door;
	while (tmp)
	{
		if (map->map[tmp->y][tmp->x] == 'D'
			&& map->map[cell_y][cell_x] != 'D')
		{
			map->map[tmp->y][tmp->x] = 'O';
			tmp = tmp->next;
		}
		else if (map->map[tmp->y][tmp->x] == 'O'
			&& map->map[cell_y][cell_x] != 'O')
		{
			map->map[tmp->y][tmp->x] = 'D';
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	render_frame(map);
}
