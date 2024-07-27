/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:01:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/27 16:21:50 by aoulahra         ###   ########.fr       */
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

int	spliter(char*str)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_split_whitespaces(str);
	while (tab[i])
	{
		if (tab[i][0] != '1' || tab[i][ft_strlen(tab[i]) - 1] != '1')
		{
			ft_putstr_fd("Error\nEmpty space isnt surrounded by walls\n", 2);
			return (0);
		}
		i++;
	}
	free_tab(&tab);
	return (1);
}

int	chek_zero(t_map *map)
{
	if (ft_strlen(map->map[map->i + 1]) <= (size_t) map->j
		|| ft_strlen(map->map[map->i - 1]) <= (size_t) map->j)
	{
		ft_putstr_fd("Error too short\n", 2);
		return (0);
	}
	if (ft_iswhitespace(map->map[map->i + 1][map->j])
			|| ft_iswhitespace(map->map[map->i - 1][map->j]))
	{
		ft_putstr_fd("Error space middle\n", 2);
		return (0);
	}
	return (1);
}
