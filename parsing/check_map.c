/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:26:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/25 18:22:37 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_tab(char ***args)
{
	int	i;

	i = 0;
	if (!*args)
		return ;
	while ((*args)[i])
	{
		free((*args)[i]);
		i++;
	}
	free(*args);
	*args = NULL;
}

void	add_last(char ***map, char *data)
{
	int		i;
	char	**new;

	i = 0;
	if (!*map)
	{
		new = (char **)ft_malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(data);
		new[1] = NULL;
		*map = new;
		return ;
	}
	i = ft_tablen(*map);
	new = (char **)ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*map)[i])
	{
		new[i] = ft_strdup((*map)[i]);
		i++;
	}
	new[i] = ft_strdup(data);
	new[i + 1] = NULL;
	free_tab(map);
	*map = new;
}

int	check_map(int fd, t_map *map)
{
	char	*line;
	// char	**map_tab;
	int		i;

	i = 0;
	// map_tab = NULL;
	skip_empty_lines(fd, map, 'm');
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		add_last(&map->map, line);
		free(line);
	}
	while (map->map[i])
	{
		printf("%s", map->map[i]);
		i++;
	}
	return (1);
}
