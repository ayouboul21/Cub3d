/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:55:51 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/30 11:31:02 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_color(t_map *map, int fd)
{
	if (map->ceiling.red < 0 || map->ceiling.red > 255
		|| map->ceiling.green < 0 || map->ceiling.green > 255
		|| map->ceiling.blue < 0 || map->ceiling.blue > 255)
	{
		ft_putstr_fd("Error\nInvalid ceiling color\n", 2);
		close(fd);
		return (0);
	}
	if (map->floor.red < 0 || map->floor.red > 255
		|| map->floor.green < 0 || map->floor.green > 255
		|| map->floor.blue < 0 || map->floor.blue > 255)
	{
		ft_putstr_fd("Error\nInvalid floor color\n", 2);
		close(fd);
		return (0);
	}
	return (1);
}

void	parse_line(char *line, t_map *map, int *ret)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		*ret = check_north(line, map);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		*ret = check_south(line, map);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		*ret = check_west(line, map);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		*ret = check_east(line, map);
	else if (line[0] == 'F' && line[1] == ' ')
		*ret = check_floor_color(line, map);
	else if (line[0] == 'C' && line[1] == ' ')
		*ret = check_ceiling_color(line, map);
}

void	fill_map(int fd, t_map *map)
{
	int		i;
	int		ret;
	char	*line;

	(1) && (i = 0, ret = 1);
	while (1)
	{
		line = skip_empty_lines(fd, map);
		if (!line)
			break ;
		parse_line(line, map, &ret);
		if (i == 5 || ret == 0)
			break ;
		(1) && (free(line), i++);
	}
	(line) && (free(line), line = NULL);
}
void initdir(t_map *map)
{
	if(map->player.dir == 'N')
		map->player.angle = 0;

	else if(map->player.dir == 'S')
		map->player.angle = 180;
	else if(map->player.dir == 'W')
		map->player.angle = 270;
	else if(map->player.dir == 'E')
		map->player.angle = 90;
}
int	parse(char *file, t_map *map)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile not found\n", 2);
		return (-1);
	}
	fill_map(fd, map);
	if (map->north == NULL || map->south == NULL || map->west == NULL
		|| map->east == NULL || map->floor_color == NULL
		|| map->ceiling_color == NULL)
	{
		close(fd);
		ft_putstr_fd("Error\nMissing information\n", 2);
		return (-1);
	}
	if (!check_color(map, fd))
		return (-1);
	if (!check_map(fd, map))
		return (-1);
	close(fd);
	initdir(map);
	return (0);
}
