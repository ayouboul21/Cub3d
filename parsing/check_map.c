/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:26:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/26 09:07:18 by hel-magh         ###   ########.fr       */
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
		add_last(&map->map, line);
		free(line);
		line = get_next_line(fd);
	}
	printer(map);
	return (1);
}
