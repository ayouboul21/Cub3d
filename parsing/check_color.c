/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:34:02 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 16:20:05 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_color(t_color *color, char *rgb)
{
	int	i;

	i = 0;
	while (ft_isdigit(rgb[i]))
		i++;
	if (rgb[i] != ',')
		return (0);
	i++;
	color->red = ft_atoi(rgb);
	rgb += i;
	i = 0;
	while (ft_isdigit(rgb[i]))
		i++;
	if (rgb[i] != ',')
		return (0);
	i++;
	color->green = ft_atoi(rgb);
	rgb += i;
	i = 0;
	while (ft_isdigit(rgb[i]))
		i++;
	if (rgb[i] != '\0')
		return (0);
	color->blue = ft_atoi(rgb + i);
	return (1);
}

int	check_floor_color(int fd, t_map *map)
{
	char	*line;
	char	**tmp;

	skip_empty_lines(fd, map, 'f');
	line = map->floor_color;
	if (line[0] != 'F' || !ft_iswhitespace(line[1]))
		return (0);
	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->floor_color = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(line);
	if (!fill_color(&map->floor, map->floor_color))
		return (0);
	if (map->floor.red < 0 || map->floor.red > 255
		|| map->floor.green < 0 || map->floor.green > 255
		|| map->floor.blue < 0 || map->floor.blue > 255)
		return (0);
	return (1);
}

int	check_ceiling_color(int fd, t_map *map)
{
	char	*line;
	char	**tmp;

	skip_empty_lines(fd, map, 'c');
	line = map->ceiling_color;
	if (line[0] != 'C' || !ft_iswhitespace(line[1]))
		return (0);
	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->ceiling_color = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(line);
	if (!fill_color(&map->ceiling, map->ceiling_color))
		return (0);
	if (map->ceiling.red < 0 || map->ceiling.red > 255
		|| map->ceiling.green < 0 || map->ceiling.green > 255
		|| map->ceiling.blue < 0 || map->ceiling.blue > 255)
		return (0);
	return (1);
}
