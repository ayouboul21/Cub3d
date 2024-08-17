/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:29:00 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/17 15:02:13 by hel-magh         ###   ########.fr       */
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
