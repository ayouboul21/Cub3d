/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:26:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/26 10:58:05 by hel-magh         ###   ########.fr       */
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
}

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

int	first_line_last(t_map *map)
{
	if (map->i == 0 || map->i == map->rows - 1)
	{
		while (map->map[map->i][map->j] == ' '
			|| map->map[map->i][map->j] == '\t')
			map->j++;
		while (map->map[map->i][map->j])
		{
			if (map->map[map->i][map->j] != '1'
				&& (!ft_iswhitespace(map->map[map->i][map->j])))
			{
				ft_putstr_fd("Error first line\n", 2);
				return (0);
			}
			map->j++;
		}
	}
	return (1);
}

int	map_validation(t_map *map)
{
	map->i = 0;
	while (map->i < map->rows)
	{
		map->j = 0;
		if (!first_line_last(map))
			return (0);
		map->i++;
	}
	return(1);
}
int	check_map(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
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
