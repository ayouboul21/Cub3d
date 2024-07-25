/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:34:02 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 14:35:01 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_floor_color(int fd, t_map *map)
{
    char	*line;
    char	**tmp;

    line = get_next_line(fd);
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
    return (1);
}

int	check_ceiling_color(int fd, t_map *map)
{
    char	*line;
    char	**tmp;

    line = get_next_line(fd);
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
    return (1);
}
