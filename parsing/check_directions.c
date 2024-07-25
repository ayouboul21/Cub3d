/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:29:00 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/25 15:52:05 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_north(int fd, t_map *map)
{
	char	*line;
	char	**tmp;

	skip_empty_lines(fd, map, 'n');
	line = map->north;
	if (line[0] != 'N' || line[1] != 'O' || !ft_iswhitespace(line[2]))
		return (0);
	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->north = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(line);
	return (1);
}

int	check_south(int fd, t_map *map)
{
	char	*line;
	char	**tmp;

	skip_empty_lines(fd, map, 's');
	line = map->north;
	if (line[0] != 'S' || line[1] != 'O' || !ft_iswhitespace(line[2]))
		return (0);
	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->south = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(line);
	return (1);
}

int	check_west(int fd, t_map *map)
{
	char	*line;
	char	**tmp;

	skip_empty_lines(fd, map, 'w');
	line = map->north;
	if (line[0] != 'W' || line[1] != 'E' || !ft_iswhitespace(line[2]))
		return (0);
	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->west = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(line);
	return (1);
}

int	check_east(int fd, t_map *map)
{
	char	*line;
	char	**tmp;

	skip_empty_lines(fd, map, 'e');
	line = map->north;
	if (line[0] != 'E' || line[1] != 'A' || !ft_iswhitespace(line[2]))
		return (0);
	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->east = ft_strdup(tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	free(line);
	return (1);
}
