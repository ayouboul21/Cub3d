/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:55:51 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/26 09:07:50 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_map(int fd, t_map *map)
{
	int		i;
	int		ret;
	char	*line;

	(1) && (i = 0, ret = 1);
	while (1)
	{
		line = skip_empty_lines(fd, map);
		if (line[0] == 'N' && line[1] == 'O')
			ret = check_north(line, map);
		else if (line[0] == 'S' && line[1] == 'O')
			ret = check_south(line, map);
		else if (line[0] == 'W' && line[1] == 'E')
			ret = check_west(line, map);
		else if (line[0] == 'E' && line[1] == 'A')
			ret = check_east(line, map);
		else if (line[0] == 'F' && line[1] == ' ')
			ret = check_floor_color(line, map);
		else if (line[0] == 'C' && line[1] == ' ')
			ret = check_ceiling_color(line, map);
		if (i == 5 || ret == 0)
			break ;
		(1) && (free(line), i++);
	}
	(line) && (free(line), line = NULL);
}

int	parse(char *file, t_map *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	fill_map(fd, map);
	if (map->north == NULL || map->south == NULL || map->west == NULL
		|| map->east == NULL || map->floor_color == NULL
		|| map->ceiling_color == NULL)
		return (-1);
	if (!check_map(fd, map))
		return (-1);
	close(fd);
	return (0);
}
