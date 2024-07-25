/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:55:51 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 14:33:47 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse(char *file, t_map *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (!check_north(fd, map))
		return (-1);
	if (!check_south(fd, map))
		return (-1);
	if (!check_west(fd, map))
		return (-1);
	if (!check_east(fd, map))
		return (-1);
	if (!check_floor_color(fd, map))
		return (-1);
	if (!check_ceiling_color(fd, map))
		return (-1);
	// if (!check_map(fd, map))
	// 	return (-1);
	close(fd);
	return (0);
}
