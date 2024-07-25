/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:34:02 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 18:18:27 by aoulahra         ###   ########.fr       */
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

int	check_floor_color(char *line, t_map *map)
{
	char	**tmp;

	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->floor_color = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	if (!fill_color(&map->floor, map->floor_color))
		return (0);
	if (map->floor.red < 0 || map->floor.red > 255
		|| map->floor.green < 0 || map->floor.green > 255
		|| map->floor.blue < 0 || map->floor.blue > 255)
		return (0);
	return (1);
}

int	check_ceiling_color(char *line, t_map *map)
{
	char	**tmp;

	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->ceiling_color = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	if (!fill_color(&map->ceiling, map->ceiling_color))
		return (0);
	if (map->ceiling.red < 0 || map->ceiling.red > 255
		|| map->ceiling.green < 0 || map->ceiling.green > 255
		|| map->ceiling.blue < 0 || map->ceiling.blue > 255)
		return (0);
	return (1);
}
