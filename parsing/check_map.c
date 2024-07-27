/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:26:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/27 16:31:23 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	printer(t_map *map)
{
	int	i;

	i = 0;
	printf("NO :%s\n", map->north);
	printf("SO :%s\n", map->south);
	printf("WE :%s\n", map->west);
	printf("EA :%s\n", map->east);
	printf("FLOOR :%s\n", map->floor_color);
	printf("CEILING :%s\n", map->ceiling_color);
	printf("MAP :\n");
	while (map->map[i])
	{
		printf("%s", map->map[i]);
		i++;
	}
	printf("\nplayer x : %d player y : %d\n", map->player.x, map->player.y);
}

int	check_line_map(t_map *map)
{
	if (!spliter(map->map[map->i]))
		return (0);
	while (map->map[map->i][map->j] == ' ' || map->map[map->i][map->j] == '\t')
		map->j++;
	if (map->map[map->i][map->j] != '1')
	{
		ft_putstr_fd("Error middle\n", 2);
		return (0);
	}
	return (1);
}

int	check_middle(t_map *map, int *i, int *j)
{
	if (*i != 0 && *i != map->rows - 1)
	{
		if (!check_line_map(map))
			return (0);
		while (map->map[*i][*j])
		{
			if (map->map[*i][*j] != '1' && map->map[*i][*j] != '0'
				&& map->map[*i][*j] != map->player.dir
				&& (!ft_iswhitespace(map->map[*i][*j])))
			{
				ft_putstr_fd("Error\nCenter of the map is invalid\n", 2);
				return (0);
			}
			if (map->map[*i][*j] == map->player.dir)
			{
				map->player.x = *j;
				map->player.y = *i;
			}
			if ((map->map[*i][*j] == '0'
				|| map->map[*i][*j] == map->player.dir) && !chek_zero(map))
				return (0);
			(*j)++;
		}
	}
	return (1);
}

int	find_direction(t_map *map)
{
	while (map->i < map->rows)
	{
		map->j = 0;
		while (map->map[map->i][map->j])
		{
			(map->map[map->i][map->j] == 'N')
				&& (map->player.dir = 'N', map->p++);
			(map->map[map->i][map->j] == 'S')
				&& (map->player.dir = 'S', map->p++);
			(map->map[map->i][map->j] == 'W')
				&& (map->player.dir = 'W', map->p++);
			(map->map[map->i][map->j] == 'E')
				&& (map->player.dir = 'E', map->p++);
			map->j++;
		}
		map->i++;
	}
	if (map->p != 1)
	{
		ft_putstr_fd("Error\nInvalid number of players\n", 2);
		return (0);
	}
	return (1);
}

int	map_validation(t_map *map)
{
	if (!find_direction(map))
		return (0);
	map->i = 0;
	map->p = 0;
	while (map->i < map->rows)
	{
		map->j = 0;
		if (!first_line_last(map) || !check_middle(map, &map->i, &map->j))
			return (0);
		map->i++;
	}
	return (1);
}

int	check_map(int fd, t_map *map)
{
	char	*line;

	line = skip_empty_lines(fd, map);
	while (1)
	{
		if (!line)
			break ;
		if (check_line(line))
		{
			free(line);
			return (0);
		}
		map->rows++;
		add_last(&map->map, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!map_validation(map))
		return (0);
	printer(map);
	return (1);
}
