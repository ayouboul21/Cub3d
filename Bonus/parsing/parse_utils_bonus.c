/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:34 by hel-magh          #+#    #+#             */
/*   Updated: 2024/08/20 15:24:57 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_remap(t_map *map)
{
	char	**new_map;

	map->i = 0;
	map->j = 0;
	new_map = (char **)ft_malloc(sizeof(char *) * (map->rows + 1));
	while (map->map[map->i])
	{
		map->j = 0;
		new_map[map->i] = ft_malloc(sizeof(char) * (map->cols + 1));
		ft_memset(new_map[map->i], ' ', map->cols);
		new_map[map->i][map->cols] = '\0';
		while (map->map[map->i][map->j] && map->map[map->i][map->j] != '\n')
		{
			new_map[map->i][map->j] = map->map[map->i][map->j];
			if (map->map[map->i][map->j] == 'D')
				ft_add_door_back(map, map->i, map->j);
			map->j++;
		}
		free(map->map[map->i]);
		map->i++;
	}
	new_map[map->rows] = NULL;
	free(map->map);
	map->map = new_map;
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	tab = (char **)ft_malloc(sizeof(char *) * (ft_strlen(str) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		k = i;
		while (str[i] && !ft_iswhitespace(str[i]))
			i++;
		if (i > k)
		{
			tab[j] = (char *)ft_malloc(i - k + 1);
			ft_strlcpy(tab[j], str + k, i - k + 1);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_iswhitespace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*skip_empty_lines(int fd, t_map *map)
{
	char	*line;

	(void)map;
	line = get_next_line(fd);
	while (line && check_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
