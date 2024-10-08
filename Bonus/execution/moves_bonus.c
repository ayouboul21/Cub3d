/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:02:38 by aoulahra          #+#    #+#             */
/*   Updated: 2024/09/04 10:48:59 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	check_diagonal(t_player *player, t_map *map, int new_x, int new_y)
{
	int		player_x;
	int		player_y;

	player_x = player->x / map->cell_width;
	player_y = player->y / map->cell_height;
	if (player_x != new_x && player_y != new_y)
	{
		if (map->map[new_y][player_x] == '1' ||
			map->map[player_y][new_x] == '1')
			return (0);
	}
	return (1);
}

void	move_forward(t_map *map)
{
	int		cell_x;
	int		cell_y;
	float	new_y;
	float	new_x;

	new_x = map->player.x + map->player.speed
		* cos((map->player.angle) * M_PI / 180.0);
	cell_x = new_x / map->cell_width;
	cell_y = map->player.y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, new_x, map->player.y, 0))
		map->player.x = new_x;
	new_y = map->player.y + map->player.speed
		* sin((map->player.angle) * M_PI / 180.0);
	cell_x = map->player.x / map->cell_width;
	cell_y = new_y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, map->player.x, new_y, 0))
		map->player.y = new_y;
}

void	move_backward(t_map *map)
{
	int		cell_x;
	int		cell_y;
	float	new_y;
	float	new_x;

	new_x = map->player.x - map->player.speed * 2
		* cos((map->player.angle) * M_PI / 180.0);
	cell_x = new_x / map->cell_width;
	cell_y = map->player.y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, new_x, map->player.y, 180.0))
		map->player.x = new_x;
	new_y = map->player.y - map->player.speed
		* sin((map->player.angle) * M_PI / 180.0);
	cell_x = map->player.x / map->cell_width;
	cell_y = new_y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, map->player.x, new_y, 180.0))
		map->player.y = new_y;
}

void	move_left(t_map *map)
{
	int		cell_x;
	int		cell_y;
	float	new_y;
	float	new_x;

	new_x = map->player.x - map->player.speed
		* cos((map->player.angle + 90) * M_PI / 180.0);
	cell_x = new_x / map->cell_width;
	cell_y = map->player.y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, new_x, map->player.y, 90))
		map->player.x = new_x;
	new_y = map->player.y - map->player.speed
		* sin((map->player.angle + 90) * M_PI / 180.0);
	cell_x = map->player.x / map->cell_width;
	cell_y = new_y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, map->player.x, new_y, 90))
		map->player.y = new_y;
}

void	move_right(t_map *map)
{
	int		cell_x;
	int		cell_y;
	float	new_y;
	float	new_x;

	new_x = map->player.x + map->player.speed
		* cos((map->player.angle + 90) * M_PI / 180.0);
	cell_x = new_x / map->cell_width;
	cell_y = map->player.y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, new_x, map->player.y, -90))
		map->player.x = new_x;
	new_y = map->player.y + map->player.speed
		* sin((map->player.angle + 90) * M_PI / 180.0);
	cell_x = map->player.x / map->cell_width;
	cell_y = new_y / map->cell_height;
	if (map->map[cell_y][cell_x] != '1' && map->map[cell_y][cell_x] != 'D'
		&& check_diagonal(&map->player, map, cell_x, cell_y)
		&& distance_to_wall(map, map->player.x, new_y, -90))
		map->player.y = new_y;
}
