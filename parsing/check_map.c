/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:26:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/26 15:33:27 by hel-magh         ###   ########.fr       */
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
int spliter(char*str)
{
	char **tab;
	int i;
	
	i = 0;
	tab = ft_split_whitespaces(str);
	while(tab[i])
	{
		
		if(tab[i][0] != '1' ||  tab[i][ft_strlen(tab[i]) - 1] != '1')
		{
			ft_putstr_fd("Error 1 on efirts and last\n", 2);
			return (0);
		}
		i++;
	}
	free_tab(&tab);
	return (1);
}
int chek_zero(t_map *map)
{
	if(ft_iswhitespace(map->map[map->i + 1][map->j]) 
		|| ft_iswhitespace(map->map[map->i - 1][map->j]))
	{
		ft_putstr_fd("Error 0\n", 2);
		return (0);
	}
	return (1);
}
int check_line_map(t_map *map)
{
	if(!spliter(map->map[map->i]))
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
int check_middle(t_map *map)
{
	if(map->i != 0 && map->i != map->rows - 1)
	{
		if(!check_line_map(map))
			return (0);
		while (map->map[map->i][map->j])
		{
			if (map->map[map->i][map->j] != '1' && map->map[map->i][map->j] != '0'
				&& map->map[map->i][map->j] != 'N' && (!ft_iswhitespace(map->map[map->i][map->j])))
			{
				ft_putstr_fd("Error middle\n", 2);
				return (0);
			}
			if(map->map[map->i][map->j] == 'N')
			{
				map->player.x = map->j;
				map->player.y = map->i;
				map->p++;
			}
			if(map->map[map->i][map->j] == '0' && !chek_zero(map))
				return(0);
			map->j++;
		}
	}
	return (1);
}

int	map_validation(t_map *map)
{
	map->i = 0;
	map->p = 0;
	while (map->i < map->rows)
	{
		map->j = 0;
		if (!first_line_last(map) || !check_middle(map))
			return (0);
		map->i++;
	}
	if(map->p != 1)
	{
		ft_putstr_fd("Error player\n", 2);
		return (0);
	}
	return(1);
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
