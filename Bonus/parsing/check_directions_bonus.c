/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:29:00 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/19 15:56:43 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

int	check_door(t_map *map, int i, int j)
{
	if (map->map[i][j] == 'D')
	{
		if ((map->map[i][j + 1] == '1' && map->map[i][j - 1] == '1' )
			|| (map->map[i + 1][j] == '1' && map->map[i - 1][j] == '1' ))
		{
			printf("good\n");
			return (0);
		}
		else
		{
			printf("Error\ndoor not surrounded by wallls\n");
			return (1);
		}
	}
	return (0);
}
