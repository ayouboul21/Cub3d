/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:29:00 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/26 17:01:58 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
