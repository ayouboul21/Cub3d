/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:14:34 by hel-magh          #+#    #+#             */
/*   Updated: 2024/07/25 13:29:44 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

	tab = (char **)malloc(sizeof(char *) * (ft_strlen(str) + 1));
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
			tab[j] = (char *)malloc(i - k + 1);
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

void	skip_empty_lines(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line && check_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		map->north = ft_strdup(line);
		free(line);
	}
}
