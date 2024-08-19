/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:29:00 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/19 15:58:39 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_north(char *line, t_map *map)
{
	int	i;

	i = 0;
	line += 2;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!i || !line[i])
		return (0);
	line += i;
	map->north = ft_substr(line, 0, ft_strlen(line) - 1);
	return (1);
}

int	check_south(char *line, t_map *map)
{
	int	i;

	i = 0;
	line += 2;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!i || !line[i])
		return (0);
	line += i;
	map->south = ft_substr(line, 0, ft_strlen(line) - 1);
	return (1);
}

int	check_west(char *line, t_map *map)
{
	int	i;

	i = 0;
	line += 2;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!i || !line[i])
		return (0);
	line += i;
	map->west = ft_substr(line, 0, ft_strlen(line) - 1);
	return (1);
}

int	check_east(char *line, t_map *map)
{
	int	i;

	i = 0;
	line += 2;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!i || !line[i])
		return (0);
	line += i;
	map->east = ft_substr(line, 0, ft_strlen(line) - 1);
	return (1);
}
