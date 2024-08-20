/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:50:25 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/20 14:14:07 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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
	t_door	*tmp;

	tmp = map->door;
	while (tmp)
	{
		if (map->map[tmp->x][tmp->y] == 'D')
		{
			map->map[tmp->x][tmp->y] = 'C';
			printf("%c\n", map->map[tmp->x][tmp->y]);
			tmp = tmp->next;
		}
		else if (map->map[tmp->x][tmp->y] == 'C')
		{
			map->map[tmp->x][tmp->y] = 'D';
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	render_frame(map);
}
