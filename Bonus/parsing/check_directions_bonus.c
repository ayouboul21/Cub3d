/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:29:00 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/18 15:23:14 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	check_north(char *line, t_map *map)
{
	char	**tmp;

	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->north = ft_strdup(tmp[1]);
	free_tab(&tmp);
	return (1);
}

int	check_south(char *line, t_map *map)
{
	char	**tmp;

	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->south = ft_strdup(tmp[1]);
	free_tab(&tmp);
	return (1);
}

int	check_west(char *line, t_map *map)
{
	char	**tmp;

	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->west = ft_strdup(tmp[1]);
	free_tab(&tmp);
	return (1);
}

int	check_east(char *line, t_map *map)
{
	char	**tmp;

	tmp = ft_split_whitespaces(line);
	if (ft_tablen(tmp) != 2)
		return (0);
	map->east = ft_strdup(tmp[1]);
	free_tab(&tmp);
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
